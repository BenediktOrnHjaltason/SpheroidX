// © copyright Benedikt Örn Hjaltason


#include "Accelerator.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAccelerator::AAccelerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	Collision->SetSphereRadius(100);
	RootComponent = Collision;

	Mesh->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void AAccelerator::BeginPlay()
{
	Super::BeginPlay();
	Spheroid = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AAccelerator::Overlaps);
	
	CurrentWorld = GetWorld();

}

// Called every frame
void AAccelerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAccelerator::Overlaps(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Spheroid->Collision->SetPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));
	Spheroid->Collision->AddImpulse(GetActorUpVector() * Accelleration);
	UGameplayStatics::PlaySound2D(GetWorld(), AcceleratorEffect);
}
