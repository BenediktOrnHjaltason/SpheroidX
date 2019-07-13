// copyright Benedikt Oern Hjaltason


#include "RadialImpulse.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

// Sets default values
ARadialImpulse::ARadialImpulse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	Center = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Center"));
	Ring = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring"));

	RootComponent = SceneRoot;
	Center->SetupAttachment(RootComponent);
	Ring->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARadialImpulse::BeginPlay()
{
	Super::BeginPlay();
	
	Spheroid = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	SetActorTickInterval(BurstFrequency);

	RingMID = Ring->CreateDynamicMaterialInstance(0);
	CenterMID = Center->CreateDynamicMaterialInstance(0);
}

// Called every frame
void ARadialImpulse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ExpandRing(RingMID);
	MorphBaseColor(CenterMID);
	GetWorldTimerManager().SetTimer(ImpulseTimer, this, &ARadialImpulse::Burst, 0.20, false);
}

void ARadialImpulse::Burst()
{
	//Must be equal to length of direction vector?
	DistanceToSpheroid = GetDistanceTo(Spheroid);

	if (DistanceToSpheroid <= EffectDistance)
	{
		DirectionVector = (Spheroid->GetActorLocation() - GetActorLocation());

		NormalizedVector = FVector(
			DirectionVector.X / DistanceToSpheroid, 
			DirectionVector.Y / DistanceToSpheroid, 
			DirectionVector.Z / DistanceToSpheroid);

		Multiplier = MultiplierBase / DistanceToSpheroid;

		Spheroid->Collision->AddImpulse(NormalizedVector * Multiplier);
	}
}