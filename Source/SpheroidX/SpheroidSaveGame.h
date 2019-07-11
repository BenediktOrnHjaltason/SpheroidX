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

		int NumberOfLevels = 48;

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
			float time_L25 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L26 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L27 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L28 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L29 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L30 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L31 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L32 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L33 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L34 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L35 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L36 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L37 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L38 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L39 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L40 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L41 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L42 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L43 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L44 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L45 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L46 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L47 = 0.f;
		UPROPERTY(VisibleAnywhere)
			float time_L48 = 0.f;


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
		UPROPERTY(VisibleAnywhere)
			bool Locked_L25 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L26 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L27 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L28 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L29 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L30 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L31 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L32 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L33 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L34 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L35 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L36 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L37 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L38 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L39 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L40 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L41 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L42 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L43 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L44 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L45 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L46 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L47 = true;
		UPROPERTY(VisibleAnywhere)
			bool Locked_L48 = true;
		//-----------/SavedData--------------//
};
