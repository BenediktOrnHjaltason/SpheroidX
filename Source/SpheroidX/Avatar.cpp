// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "Kismet/KismetMathLibrary.h"
#include "LevelTransitionDevice.h"
#include "SpheroidXGameModeBase.h"
#include "EngineUtils.h"

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

	RootComponent = Collision;

	Collision->SetSphereRadius(32);
	
	PlaneMesh->SetupAttachment(Collision);
	Thruster->SetupAttachment(Collision);
	SpringArm->SetupAttachment(Collision);
	Camera->SetupAttachment(SpringArm);
	Exhaust->SetupAttachment(Collision);
	
}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();

	ExhaustMID = Exhaust->CreateDynamicMaterialInstance(0);
	GameModeRef = Cast<ASpheroidXGameModeBase>(GetWorld()->GetAuthGameMode());

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
		

	//UE_LOG(LogTemp, Warning, TEXT("Degrees: %f"), DegreesXRotation)

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
	//UE_LOG(LogTemp, Warning, TEXT("X-value: %f"),AxisValue)
}

void AAvatar::SpheroidYAxis(float AxisValue)
{
	SpheroidYValue = AxisValue;
	//UE_LOG(LogTemp, Warning, TEXT("Y-value: %f"), AxisValue)
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
	if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic)
	{
		GameModeRef->PlayHUDCountdown();
		DeathSequence();
	}
}

void AAvatar::DeathSequence()
{
	Collision->SetLinearDamping(1000);
	SetActorHiddenInGame(true);
	DeathLocation = GetActorLocation();
}

void AAvatar::MoveToEntrance(float Timeline)
{
	SetActorLocation(UKismetMathLibrary::VLerp(DeathLocation, EntranceAttachLoc, Timeline));
}