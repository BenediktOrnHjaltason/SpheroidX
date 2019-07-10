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

		int NumberOfLevels = 24;

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
			float time_L10 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L11 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L12 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L13 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L14 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L15 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L16 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L17 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L18 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L19 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L20 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L21 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L22 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L23 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L24 = 0.f;


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
		UPROPERTY(VisibleAnywhere)
			bool Locked_L10 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L11 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L12 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L13 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L14 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L15 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L16 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L17 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L18 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L19 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L20 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L21 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L22 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L23 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L24 = true;

		//-----------/SavedData--------------//
};
