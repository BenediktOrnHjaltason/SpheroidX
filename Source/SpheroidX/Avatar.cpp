// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "Kismet/KismetMathLibrary.h"

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

	RootComponent = Collision;

	Collision->SetSphereRadius(32);

	PlaneMesh->SetupAttachment(Collision);
	Thruster->SetupAttachment(Collision);
	SpringArm->SetupAttachment(Collision);
	Camera->SetupAttachment(SpringArm);
	
}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	
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

	SetActorRotation(FRotator(0.f, 0.f, UKismetMathLibrary::DegAtan2(SpheroidXValue, SpheroidYValue)));


	//UE_LOG(LogTemp, Warning, TEXT("Degrees: %f"), DegreesXRotation)

}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("SpheroidX", this, &AAvatar::SpheroidXAxis);
	PlayerInputComponent->BindAxis("SpheroidY", this, &AAvatar::SpheroidYAxis);

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
