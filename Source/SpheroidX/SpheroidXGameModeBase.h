// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyEnums.h"
#include "SpheroidXGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPHEROIDX_API ASpheroidXGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AAvatar* Spheroid;

	//-------HUD-animations
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void PlayHUDAnimation(EHUDAnimations Animation);


	//-------CameraShakes
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void PlayCameraShake(ECameraShakes CameraShake);

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void NotifiedOfDeath();

};


