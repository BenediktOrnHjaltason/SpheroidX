// copyright Benedikt Örn Hjaltason

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

		UPROPERTY(VisibleAnywhere)
		uint32 UserIndex;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString SaveSlotName;


		TArray<float*> LevelTimes;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float time_L1 = 0.f;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float time_L2 = 0.f;


};
