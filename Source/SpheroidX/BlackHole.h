// copyright Benedikt Orn Hjaltason

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ChildActorComponent.h"
#include "BlackHole.generated.h"

UCLASS()
class SPHEROIDX_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHole();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Plane;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Torus;

	UPROPERTY(VisibleAnywhere)
		USphereComponent* Collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UChildActorComponent* MeasureActor;

	class AAvatar* Spheroid;
	UWorld* CurrentWorld;

	float CurrentDistanceToSpheroid;
	float AttractScale;
	float ForceBase = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float radius = 0;

	bool SpheroidIsgrabbed;

	FVector CurrentLocationThis;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
