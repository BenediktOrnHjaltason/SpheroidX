// copyright Benedikt Örn Hjaltason


#include "SpheroidGameInstance.h"


/*
GameInstance holds HighScore times

*/

USpheroidGameInstance::USpheroidGameInstance()
{
	LevelTimes.Init(0.f, NumberOfLevels);
	LevelTimesMinutes.Init(0, NumberOfLevels);
	LevelTimesSeconds.Init(0, NumberOfLevels);
	LevelTimesRemaining.Init(0, NumberOfLevels);

	LevelsLocked.Init(true, NumberOfLevels);
}

float USpheroidGameInstance::GetLevelTime(int LevelIndex)
{
	return LevelTimes[LevelIndex];
}

void USpheroidGameInstance::SetLevelTime(int LevelIndex, float NewTime)
{
	LevelTimes[LevelIndex] = NewTime;
}

void USpheroidGameInstance::BreakTime(float& f_Seconds, int& Minutes, int& Seconds, int& Remainder)
{
	//int
	Minutes = f_Seconds / 60;
	//int
	Seconds = f_Seconds - (Minutes * 60);
	//float
	Remainder = (f_Seconds - Seconds) * 100;

	PrintLevel0Times();
}


void USpheroidGameInstance::SaveLevelTimeToDisk()
{
	if (LevelTimes.IsValidIndex(0))
	{

		USpheroidSaveGame* SaveObject = Cast<USpheroidSaveGame>(UGameplayStatics::CreateSaveGameObject(USpheroidSaveGame::StaticClass()));

		for (int i = 0; i < NumberOfLevels; ++i)
		{
			*SaveObject->LevelTimes[i] = LevelTimes[i];
			*SaveObject->LevelsLocked[i] = LevelsLocked[i];
		}

		UGameplayStatics::SaveGameToSlot(SaveObject, SlotName, UserIndex);
	}

}

void USpheroidGameInstance::LoadLevelTimesFromDisk()
{
	if (bIsFreshSessionStart && UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
	{
		bIsFreshSessionStart = false;

		USpheroidSaveGame* LoadObject = Cast<USpheroidSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));

		if (LoadObject)
		{
			for (int i = 0; i < NumberOfLevels; ++i)
			{
				if (LevelTimes.IsValidIndex(i) && LoadObject->LevelTimes.IsValidIndex(i) &&
					LevelsLocked.IsValidIndex(i) && LoadObject->LevelsLocked.IsValidIndex(i))
				{   
					LevelTimes[i] = *LoadObject->LevelTimes[i];
					LevelsLocked[i] = *LoadObject->LevelsLocked[i];

					BreakTime(LevelTimes[i], LevelTimesMinutes[i], LevelTimesSeconds[i], LevelTimesRemaining[i]);
				}
			}
		}
	}
}