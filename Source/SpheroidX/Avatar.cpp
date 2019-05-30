// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "Kismet/KismetMathLibrary.h"
#include "LevelTransitionDevice.h"
#include "SpheroidXGameModeBase.h"
#include "EngineUtils.h"
#include "Kismet/KismetMaterialLibrary.h"

// Sets default values
AAvatar::AAvatar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Image Plane"));
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	Thruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("Thruster"));
	Exhaust = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Exhaust"));
	EffectPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EffectPlane"));

	RootComponent = Collision;

	Collision->SetSphereRadius(32);
	
	PlaneMesh->SetupAttachment(Collision);
	Thruster->SetupAttachment(Collision);
	SpringArm->SetupAttachment(Collision);
	Camera->SetupAttachment(SpringArm);
	Exhaust->SetupAttachment(Collision);
	EffectPlane->SetupAttachment(Collision);
	
}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();

	CurrentWorld = GetWorld();
	GameModeRef = Cast<ASpheroidXGameModeBase>(GetWorld()->GetAuthGameMode());

	ExhaustMID = Exhaust->CreateDynamicMaterialInstance(0);
	//EffectMID = EffectPlane->CreateDynamicMaterialInstance(0);

	MaterialParameters = LoadObject<UMaterialParameterCollection>(NULL, TEXT("MaterialParameterCollection'/Game/Materials/Avatar/MaterialParameterCollection_Spheroid.MaterialParameterCollection_Spheroid'"),
		NULL, LOAD_None, NULL);

	if (MaterialParameters) UE_LOG(LogTemp, Warning, TEXT("BeginPlay: We have reference to MaterialParameterCollection"));
	

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AAvatar::Overlaps);

	for (TActorIterator<ALevelTransitionDevice> DeviceItr(GetWorld()); DeviceItr; ++DeviceItr)
	{
		ALevelTransitionDevice *Device = *DeviceItr;
		if (Device->EntranceOrExit == ELTD_Type::Exit)
		{
			LevelExit = Device;
			ExitAttachLoc = LevelExit->PawnAttachLocation->GetComponentLocation();
		}
		else if (Device->EntranceOrExit == ELTD_Type::Entrance)
		{
			LevelEntrance = Device;
			EntranceAttachLoc = LevelEntrance->PawnAttachLocation->GetComponentLocation();
		}
	}
}

// Called every frame
void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InputMultiplier = UKismetMathLibrary::Sqrt(
		UKismetMathLibrary::MultiplyMultiply_FloatFloat(SpheroidXValue, 2)
		+ UKismetMathLibrary::MultiplyMultiply_FloatFloat(SpheroidYValue, 2));

	if (InputMultiplier > 1) InputMultiplier = 1;
	
	Thruster->ThrustStrength = InputMultiplier * BaseThrustStrength;

	if (InputMultiplier > 0.3)
		SetActorRotation(FRotator(0.f, 0.f, UKismetMathLibrary::DegAtan2(SpheroidXValue, SpheroidYValue)));

	
	ExhaustMID->SetScalarParameterValue("Opacity", InputMultiplier);
	Exhaust->SetRelativeScale3D(FVector(0.5f, UKismetMathLibrary::Lerp(0.5f, 1.0f, InputMultiplier), 1));
		
}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("SpheroidX", this, &AAvatar::SpheroidXAxis);
	PlayerInputComponent->BindAxis("SpheroidY", this, &AAvatar::SpheroidYAxis);
	PlayerInputComponent->BindAction("StopMomentum", IE_Pressed, this, &AAvatar::StopMomentum);
}

void AAvatar::SpheroidXAxis(float AxisValue)
{
	SpheroidXValue = AxisValue;
}

void AAvatar::SpheroidYAxis(float AxisValue)
{
	SpheroidYValue = AxisValue;
}

void AAvatar::IncrementKeys()
{
	++Keys;

	if (Keys >= LevelExit->KeysNeededToOpen)
	{
		LevelExit->TL_OperateDoors(EOpenOrClose::Open);
	}
}

void AAvatar::StopMomentum()
{
	Collision->SetAllPhysicsLinearVelocity(FVector(0, 0, 0));
}

void AAvatar::Overlaps(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//Collidig with structure
	if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic)
	{
		UKismetMaterialLibrary::SetVectorParameterValue(CurrentWorld, MaterialParameters, "Effect_Color", DeathColor);

		DeathSequence();
	}
}

void AAvatar::DeathSequence()
{	
	UKismetMaterialLibrary::SetScalarParameterValue(CurrentWorld, MaterialParameters, "Effect_Opacity", 1);
	TL_DeathEffect();
	Collision->SetLinearDamping(1000);
	PlaneMesh->SetVisibility(false);
	Exhaust->SetVisibility(false);
	DeathLocation = GetActorLocation();
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);

	GetWorldTimerManager().SetTimer(MoveToEntranceHandle, this, &AAvatar::TL_MoveToEntrance, 1.25f, false);
}

void AAvatar::MoveToEntrance(float Timeline)
{
	SetActorLocation(UKismetMathLibrary::VLerp(DeathLocation, EntranceAttachLoc, Timeline));
}

void AAvatar::AfterMove()
{
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	LevelEntrance->TL_OperateDoors(EOpenOrClose::Close, true);
}


void AAvatar::DeathEffect(float TimelineScale)
{
	EffectPlane->SetRelativeScale3D(UKismetMathLibrary::VLerp(Small, Big, TimelineScale));
}

void AAvatar::DeathEffectCleanUp()
{
	UKismetMaterialLibrary::SetScalarParameterValue(CurrentWorld, MaterialParameters, "Effect_Opacity", 0);
}