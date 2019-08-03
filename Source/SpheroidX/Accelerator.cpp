// copyright Benedikt Orn Hjaltason


#include "Accelerator.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAccelerator::AAccelerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = BoxCollision;

	Mesh->SetupAttachment(BoxCollision);

	BoxCollision->SetBoxExtent(FVector(130.f, 130.f, 30.f));
	
}

// Called when the game starts or when spawned
void AAccelerator::BeginPlay()
{
	Super::BeginPlay();

	Spheroid = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	//Collision->OnComponentBeginOverlap.RemoveDynamic(this, &AAccelerator::Overlaps);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAccelerator::OverlapsWithSpheroid);
	CurrentWorld = GetWorld();
}

// Called every frame
void AAccelerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AAccelerator::OverlapsWithSpheroid(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	Spheroid->Collision->SetPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));
	Spheroid->Collision->AddImpulse(GetActorUpVector() * Accelleration);
	PlaySoundEffect();
}


