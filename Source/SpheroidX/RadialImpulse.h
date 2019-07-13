// copyright Benedikt Oern Hjaltason

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Avatar.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "RadialImpulse.generated.h"

UCLASS()
class SPHEROIDX_API ARadialImpulse : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARadialImpulse();

	UPROPERTY(EditAnywhere)
		USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Center;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Ring;

	AAvatar* Spheroid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Burst)
		float EffectDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Burst)
		float BurstFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Burst)
		float MultiplierBase;

	float Multiplier = 0;;

	float DistanceToSpheroid = 0;

	FVector DirectionVector{ 0.f, 0.f, 0.f };
	FVector NormalizedVector{ 0.f, 0.f, 0.f };

	FTimerHandle ImpulseTimer;

	UMaterialInstanceDynamic* RingMID;


	UMaterialInstanceDynamic* CenterMID;


	//Expands ring and sets opacity
	UFUNCTION(BlueprintImplementableEvent)
		void ExpandRing(UMaterialInstanceDynamic* MID);

	UFUNCTION(BlueprintImplementableEvent)
		void MorphBaseColor(UMaterialInstanceDynamic* MID);

	void Burst();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
