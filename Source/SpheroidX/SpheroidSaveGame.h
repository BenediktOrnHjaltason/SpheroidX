// copyright Benedikt Orn Hjaltason

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

		int NumberOfLevels = 9;

		TArray<float*> LevelTimes;
		TArray<bool*> LevelsLocked;

		UPROPERTY(VisibleAnywhere)
			float time_L1 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L2 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L3 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L4 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L5 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L6 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L7 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L8 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L9 = 0.f;


		UPROPERTY(VisibleAnywhere)
			bool Locked_L1 = false;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L2 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L3 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L4 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L5 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L6 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L7 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L8 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L9 = true;

		//-----------/SavedData--------------//
};
