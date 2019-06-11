// copyright Benedikt Örn Hjaltason

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SpheroidSaveGame.h"
#include "SpheroidGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPHEROIDX_API USpheroidGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	USpheroidGameInstance();

	USpheroidSaveGame* SaveObject;

	UFUNCTION(BlueprintCallable)
		void SaveLevelTimeToDisk();

	UFUNCTION(BlueprintCallable)
	void LoadLevelTimesFromDisk();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfLevels;

	UFUNCTION(BlueprintCallable)
	void PrintLevel0Times()
	{
		UE_LOG(LogTemp, Warning, TEXT("Minutes: %i"), LevelTimesMinutes[0])
		UE_LOG(LogTemp, Warning, TEXT("Seconds: %i"), LevelTimesSeconds[0])
		UE_LOG(LogTemp, Warning, TEXT("Remainder: %i"), LevelTimesRemaining[0])
	}

	//-----------Level times----------//

	TArray<float> LevelTimes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<int> LevelTimesMinutes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<int> LevelTimesSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<int> LevelTimesRemaining;

	UFUNCTION(BlueprintCallable)
		int GetLevelTimeMinutes(int LevelIndex) { return LevelTimesMinutes[LevelIndex]; }

	UFUNCTION(BlueprintCallable)
		int GetLevelTimeSeconds(int LevelIndex) { return LevelTimesSeconds[LevelIndex]; }

	UFUNCTION(BlueprintCallable)
		int GetLevelTimeRemaining(int LevelIndex) { return LevelTimesRemaining[LevelIndex]; }


	void BreakTime(float& f_Seconds, int& Minutes, int& Seconds, int& Remainder);

	float GetLevelTime(int LevelIndex);
	void SetLevelTime(int LevelIndex, float NewTime);

};
