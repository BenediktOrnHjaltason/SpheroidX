// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "LevelTransitionDevice.generated.h"

UCLASS()
class SPHEROIDX_API ALevelTransitionDevice : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelTransitionDevice();

	UPROPERTY(EditAnywhere)
		USphereComponent* Collision;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Base;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* LeftDoor;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* RightDoor;

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundBase* OpenDoors;

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundBase* Thonk;

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundBase* ReceiveSpheroid;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
