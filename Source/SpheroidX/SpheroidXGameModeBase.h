// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "SpheroidXGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPHEROIDX_API ASpheroidXGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
		void PlayHUDCountdown();

	UFUNCTION(BlueprintImplementableEvent)
		void PlayHUD_Anim_ReachedGoal();
};


