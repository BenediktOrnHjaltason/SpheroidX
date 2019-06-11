// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyEnums.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialParameterCollection.h"
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

	//Colors for active status

	UMaterialParameterCollection* MaterialParameters;

	FVector Status_Active = { 0.f, 0.3589754f, 0.6802084f };
	FVector Status_Inactive = { 0.052083f, 0.052083f, 0.052083f };

	UFUNCTION(BlueprintCallable)
	void Status_TurnToActive();

	UFUNCTION(BlueprintCallable)
	void Status_TurnToInactive();

	UWorld* CurrentWorld;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsTutorialLevel = false;

	void ResetPickups();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int LevelIndex = 0;

};


