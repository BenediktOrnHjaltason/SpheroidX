// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransitionDevice.h"
#include "Kismet/KismetMathLibrary.h"
#include "Avatar.h"
#include "SpheroidXGameModeBase.h"
#include "Kismet/GameplayStatics.h"


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

	RootComponent = Collision;
	Collision->SetSphereRadius(40);

	Base->SetupAttachment(Collision);
	LeftDoor->SetupAttachment(Collision);
	RightDoor->SetupAttachment(Collision);
	PawnAttachLocation->SetupAttachment(Collision);

}

// Called when the game starts or when spawned
void ALevelTransitionDevice::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ALevelTransitionDevice::CatchSpheroid);

	Spheroid = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	GameModeRef = Cast<ASpheroidXGameModeBase>(GetWorld()->GetAuthGameMode());

	CreateHUD();

	if (EntranceOrExit == ELTD_Type::Entrance)
	{
		if (Spheroid) PrepareSpheroidForLaunch();
		GetWorldTimerManager().SetTimer(ShootOutSequenceTimer, this, &ALevelTransitionDevice::ShootOutSequence, 2.f, false);
		
	}

	else if (EntranceOrExit == ELTD_Type::Exit && KeysNeededToOpen <= 0) TL_OperateDoors(EOpenOrClose::Open);
}

// Called every frame
void ALevelTransitionDevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelTransitionDevice::PrepareSpheroidForLaunch()
{
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
	GameModeRef->PlayHUDCountdown();

	TL_OperateDoors(EOpenOrClose::Open);

	GetWorldTimerManager().SetTimer(StartImpulseTimer, this, &ALevelTransitionDevice::ShootOutSpheroid, 3.f, false);
}

void ALevelTransitionDevice::ShootOutSpheroid()
{
	//Spheroid->Collision->SetEnableGravity(true);
	Spheroid->Collision->SetLinearDamping(0);

	Spheroid->Collision->AddImpulse(GetActorUpVector() * 15000);

	GetWorldTimerManager().SetTimer(EnableSpheroidInputTimer, this, &ALevelTransitionDevice::ReactivateSpheroidInput, 1.1f, false);
}

void ALevelTransitionDevice::ReactivateSpheroidInput()
{
	Spheroid->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void ALevelTransitionDevice::CatchSpheroid(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (EntranceOrExit == ELTD_Type::Entrance) return;

	Spheroid->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	Spheroid->SetActorTickEnabled(false);
	Spheroid->ExhaustMID->SetScalarParameterValue("Opacity", 0.f);

	Spheroid->SetActorLocation(PawnAttachLocation->GetComponentLocation());
	Spheroid->AttachToComponent(PawnAttachLocation, FAttachmentTransformRules(
	EAttachmentRule::SnapToTarget, false));

	Spheroid->Collision->SetLinearDamping(1000.f);
	Spheroid->Collision->SetAngularDamping(1000.f);
	Spheroid->Collision->SetEnableGravity(false);
	//Spheroid->Collision->SetSimulatePhysics(false);

	TL_OperateDoors(EOpenOrClose::Close);
}