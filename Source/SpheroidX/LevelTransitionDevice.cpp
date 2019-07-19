// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransitionDevice.h"
#include "Kismet/KismetMathLibrary.h"
#include "Avatar.h"
#include "SpheroidXGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"


// Sets default values
ALevelTransitionDevice::ALevelTransitionDevice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left door"));
	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right door"));
	PawnAttachLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Spheroid Attach"));
	BlinkingLight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blinking Light"));

	RootComponent = Collision;
	Collision->SetSphereRadius(60);

	Base->SetupAttachment(Collision);
	LeftDoor->SetupAttachment(Collision);
	RightDoor->SetupAttachment(Collision);
	PawnAttachLocation->SetupAttachment(Collision);
	BlinkingLight->SetupAttachment(Collision);

}

// Called when the game starts or when spawned
void ALevelTransitionDevice::BeginPlay()
{
	Super::BeginPlay();

	CurrentWorld = GetWorld();
	Spheroid = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	MaterialParameters = LoadObject<UMaterialParameterCollection>(NULL, TEXT("MaterialParameterCollection'/Game/Materials/MaterialParameterCollection_Spheroid.MaterialParameterCollection_Spheroid'"),
		NULL, LOAD_None, NULL);

	SetActorTickInterval(0.75);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ALevelTransitionDevice::CatchSpheroid);

	
	GameModeRef = Cast<ASpheroidXGameModeBase>(GetWorld()->GetAuthGameMode());


	if (EntranceOrExit == ELTD_Type::Entrance)
	{
		FString MapName = GetWorld()->GetMapName();

		if (MapName.Contains("B")) CreateHUD(false);
		else CreateHUD();

		if (Spheroid) PrepareSpheroidForLaunch();
		GetWorldTimerManager().SetTimer(ShootOutSequenceTimer, this, &ALevelTransitionDevice::ShootOutSequence, 2.f, false);

		SetActorTickEnabled(false);
		BlinkingLight->SetVisibility(false);
	}

	else if (EntranceOrExit == ELTD_Type::Exit && KeysNeededToOpen <= 0) TL_OperateDoors(EOpenOrClose::Open);

	else if (EntranceOrExit == ELTD_Type::TutorialExit)
	{

		UE_LOG(LogTemp, Warning, TEXT("LTD::BeginPlay(): TutorialExit detected"))
		TL_OperateDoors(EOpenOrClose::Open, false, true);
	}
	
}

// Called every frame
void ALevelTransitionDevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DummyBool = !DummyBool;

	if (DummyBool) BlinkingLight->SetVisibility(true,true);
	else BlinkingLight->SetVisibility(false,true);
}

void ALevelTransitionDevice::PrepareSpheroidForLaunch()
{
	Spheroid->SetActorTickEnabled(false);
	Spheroid->Exhaust->SetVisibility(false);
	Spheroid->PlaneMesh->SetRelativeScale3D(FVector(0.837413f, 0.837413f, 1.000000f));

	Spheroid->PlaneMesh->SetVisibility(true);
	Spheroid->EffectPlane->SetVisibility(true);

	Spheroid->SetActorRotation(FRotator(0.f, 0.f, 0.f));

	Spheroid->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Spheroid->Collision->SetLinearDamping(1000.f);

	Spheroid->AttachToComponent(PawnAttachLocation, FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget, false));
}

void ALevelTransitionDevice::OperateDoors(EOpenOrClose OpenOrClose, float Timeline)
{
	if (OpenOrClose == EOpenOrClose::Open)
	{
		LeftDoor->SetRelativeRotation(UKismetMathLibrary::RLerp(LeftDoorClosed, LeftDoorOpen, Timeline, true));
		RightDoor->SetRelativeRotation(UKismetMathLibrary::RLerp(RightDoorClosed, RightDoorOpen, Timeline, true));
	}
	else
	{
		LeftDoor->SetRelativeRotation(UKismetMathLibrary::RLerp(LeftDoorOpen, LeftDoorClosed, Timeline, true));
		RightDoor->SetRelativeRotation(UKismetMathLibrary::RLerp(RightDoorOpen, RightDoorClosed, Timeline, true));
	}
}

void ALevelTransitionDevice::ShootOutSequence()
{
	if (Spheroid->bIsFirstTimeOnLevel)
	{
		GameModeRef->PlayHUDAnimation(EHUDAnimations::CountDown);

		TL_OperateDoors(EOpenOrClose::Open);

		GetWorldTimerManager().SetTimer(StartImpulseTimer, this, &ALevelTransitionDevice::ShootOutSpheroid, 3.f, false);
	}

	else
	{
		GameModeRef->PlayHUDAnimation(EHUDAnimations::RespawnGo);
		TL_OperateDoors(EOpenOrClose::Open, true);
		GetWorldTimerManager().SetTimer(StartImpulseTimer, this, &ALevelTransitionDevice::ShootOutSpheroid, 1.f, false);
	}
}

void ALevelTransitionDevice::ShootOutSpheroid()
{
	Spheroid->Collision->SetLinearDamping(0);
	Spheroid->Collision->SetPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));

	
	Spheroid->Collision->AddImpulse(GetActorUpVector() * 14000);

	ReactivateSpheroidInput();
}

void ALevelTransitionDevice::ReactivateSpheroidInput()
{
	Spheroid->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	Spheroid->bIsDeathSequenceRunning = false;
	
	Spheroid->SetActorTickEnabled(true);
	Spheroid->Exhaust->SetVisibility(true);
	Spheroid->bIsEffectAllowed = true;

	if (!GameModeRef->bIsTutorialLevel)
	Spheroid->TimeAtShootOut = CurrentWorld->GetRealTimeSeconds();
}

void ALevelTransitionDevice::CatchSpheroid(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (EntranceOrExit == ELTD_Type::Exit || EntranceOrExit == ELTD_Type::TutorialExit)
	{

		UGameplayStatics::PlaySound2D(GetWorld(), Sound_ReachedGoal);

		Spheroid->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		Spheroid->SetActorTickEnabled(false);
		Spheroid->ExhaustMID->SetScalarParameterValue("Opacity", 0.f);
		Spheroid->Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);

		Spheroid->SetActorLocation(PawnAttachLocation->GetComponentLocation());
		Spheroid->AttachToComponent(PawnAttachLocation, FAttachmentTransformRules(
			EAttachmentRule::SnapToTarget, false));

		Spheroid->Collision->SetLinearDamping(1000.f);
		Spheroid->Collision->SetAngularDamping(1000.f);
		Spheroid->AudioComp->SetVolumeMultiplier(0.f);

		TL_OperateDoors(EOpenOrClose::Close);

		GameModeRef->PlayHUDAnimation(EHUDAnimations::ReachedGoal);

		if (EntranceOrExit == ELTD_Type::TutorialExit)
		{
			CreateTutorialEndWidget();
		}
	}
}

void ALevelTransitionDevice::SetLightToGreen()
{
	SetActorTickEnabled(false);
	BlinkingLight->SetVisibility(true);
	UKismetMaterialLibrary::SetVectorParameterValue(CurrentWorld, MaterialParameters, "Device_BlinkingLight", GreenLight);
	
}

void ALevelTransitionDevice::DeactivateExit()
{
	SetActorTickEnabled(true);
	UKismetMaterialLibrary::SetVectorParameterValue(CurrentWorld, MaterialParameters, "Device_BlinkingLight", RedLight);
	SetActorTickEnabled(true);

	TL_OperateDoors(EOpenOrClose::Close);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

}