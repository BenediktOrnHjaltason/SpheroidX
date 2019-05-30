// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Pickup_Key.generated.h"

/**
 * 
 */
UCLASS()
class SPHEROIDX_API APickup_Key : public APickupBase
{
	GENERATED_BODY()

public:

	APickup_Key();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void PlayPickupSound() override;

	UMaterialInstanceDynamic* GrowerMID;

	FVector GrowerScale;

	UPROPERTY(EditAnywhere)
	USoundBase* Sound_Pickup;

	UFUNCTION(BlueprintImplementableEvent)
		void TL_RuntimeEffect();

	UFUNCTION(BlueprintCallable)
		void RuntimeEffect(float Grower, float MID_Opacity);

	
};
