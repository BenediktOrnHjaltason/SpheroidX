// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransitionDevice.h"

// Sets default values
ALevelTransitionDevice::ALevelTransitionDevice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left door"));
	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right door"));

	RootComponent = Collision;
	Collision->SetSphereRadius(40);

	Base->SetupAttachment(Collision);
	LeftDoor->SetupAttachment(Collision);
	RightDoor->SetupAttachment(Collision);

}

// Called when the game starts or when spawned
void ALevelTransitionDevice::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelTransitionDevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

