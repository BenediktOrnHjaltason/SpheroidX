// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyEnums.h"
#include "PickupBase.generated.h"

UCLASS()
class SPHEROIDX_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBase();

	UPROPERTY(EditAnywhere)
	USphereComponent* Collision;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* EffectPlane;



	UPROPERTY(EditAnywhere)
	EPickupType PickupType;

	class AAvatar* Spheroid;

	UFUNCTION()
		void PickedUp(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
			UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	virtual void PlayPickupSound();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
