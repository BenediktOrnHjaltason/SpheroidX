// copyright Benedikt Orn Hjaltason

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

	FString SlotName = TEXT("SpheroidOne");
	uint32 UserIndex = 0;

	int NumberOfLevels = 24;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Levels)
		int LevelIndex = 0;

	bool bIsFreshSessionStart = true;

	UFUNCTION(BlueprintCallable)
		void SaveLevelTimesToDisk();

	UFUNCTION(BlueprintCallable)
	void LoadLevelTimesFromDisk();


	//-----------Level times----------//

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<float> LevelTimes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<bool> LevelsLocked;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FString> LevelTimesString;

	//--Temp variable--//

	int i_Minutes = 0;
	FString S_Minutes = "";
	int i_Seconds = 0;
	FString S_Seconds = "";
	FString S_Milliseconds = "";
	//------------------//

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float fCurrentLevelTime{ 0.f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float OldTimeForComparison{ 0.f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString sCurrentLevelTime{"00 : 00 : 00"};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString sPreviousBestTime{"00 : 00 : 00"};

	void ManageNewHighScore(float NewTime);


	void BreakTimeLevelEnd(const float& f_Seconds, const int&p_LevelIndex);

	void BreakTimeLoad(const float& f_Seconds, const int&LevelIndex);

	float GetLevelTime() { return LevelTimes[LevelIndex]; }
	void SetLevelTime(float NewTime) { LevelTimes[LevelIndex] = NewTime; }

	UFUNCTION(BlueprintCallable)
	void ResetAllLevelTimes();

};
