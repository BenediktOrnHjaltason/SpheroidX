﻿// copyright Benedikt Orn Hjaltason

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SpheroidSaveGame.generated.h"

/**
 * 
 */


UCLASS()
class SPHEROIDX_API USpheroidSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

		USpheroidSaveGame();

		UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

		UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

		//-------------SavedData-------------//

		TArray<float*> LevelTimes;
		TArray<bool*> LevelsLocked;

		UPROPERTY(VisibleAnywhere)
			float time_L1 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L2 = 0.f;


		UPROPERTY(VisibleAnywhere)
			bool Locked_L1 = false;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L2 = true;

		//-----------/SavedData--------------//
};
