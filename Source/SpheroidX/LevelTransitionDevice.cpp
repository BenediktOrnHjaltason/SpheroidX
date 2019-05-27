// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransitionDevice.h"
#include "Kismet/KismetMathLibrary.h"
#include "Avatar.h"
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

	Spheroid = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (EntranceOrExit == ELTD_Type::Entrance)
	{
		Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		if (Spheroid)
		{
			Spheroid->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(),0));
			Spheroid->AttachToComponent(PawnAttachLocation, FAttachmentTransformRules(
				EAttachmentRule::SnapToTarget, false));
		}
		
		TL_OperateDoors(EOpenOrClose::Open);

		GetWorldTimerManager().SetTimer(StartImpulseTimer, this, &ALevelTransitionDevice::ShootOutSpheroid, 4.f, false);
	}
}

// Called every frame
void ALevelTransitionDevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void ALevelTransitionDevice::ShootOutSpheroid()
{
	Spheroid->Collision->AddImpulse(GetActorUpVector() * 10000);
	GetWorldTimerManager().SetTimer(EnableSpheroidInputTimer, this, &ALevelTransitionDevice::ReactivateSpheroidInput, 1.f, false);
}

void ALevelTransitionDevice::ReactivateSpheroidInput()
{
	Spheroid->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}