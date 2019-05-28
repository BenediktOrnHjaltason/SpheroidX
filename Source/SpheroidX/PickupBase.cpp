// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupBase.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	EffectPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Effect Plane"));

	Collision->SetSphereRadius(27);
	RootComponent = Collision;

	Mesh->SetupAttachment(Collision);
	EffectPlane->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	Spheroid = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	Collision->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::PickUp);
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupBase::PickUp(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp,Warning, TEXT("PICKED UP MOTHAFOCKA!"))

	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorHiddenInGame(true);

	if (PickupType == EPickupType::Key)
	{
		Spheroid->IncrementKeys();
	}

}