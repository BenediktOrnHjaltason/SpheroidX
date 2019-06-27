// copyright Benedikt Örn Hjaltason


#include "SpheroidGameInstance.h"
#include "Kismet/KismetStringLibrary.h"
#include "UnrealString.h"


/*
GameInstance holds HighScore times

*/

USpheroidGameInstance::USpheroidGameInstance()
{
	LevelTimes.Init(0.f, NumberOfLevels);

	LevelTimesString.Init("00 : 00 : 00", NumberOfLevels);

	LevelsLocked.Init(true, NumberOfLevels);
}

void USpheroidGameInstance::BreakTime(float& f_Seconds, int& p_LevelIndex)
{
	//Minutes

	i_Minutes = f_Seconds / 60;
	S_Minutes = FString::FromInt(i_Minutes);

	if (S_Minutes.Len() < 2) S_Minutes = "0" + S_Minutes;

	//Seconds

	i_Seconds = f_Seconds - i_Minutes;

	S_Seconds = FString::FromInt(i_Seconds);

	if (S_Seconds.Len() < 2) S_Seconds = "0" + S_Seconds;

	//Milliseconds

	S_Milliseconds = FString::SanitizeFloat(f_Seconds, 2);

	for (int i = 0; i < S_Milliseconds.Len(); ++i)
	{
		if (UKismetStringLibrary::GetSubstring(S_Milliseconds, i, 1) == ".")
		{
			S_Milliseconds = UKismetStringLibrary::GetSubstring(S_Milliseconds, i+1, 2);
			break;
		}
	}

	LevelTimesString[p_LevelIndex] = S_Minutes + " : " + S_Seconds + " : " + S_Milliseconds;
	
	UE_LOG(LogTemp,Warning, TEXT("TimeString = %s"), *LevelTimesString[p_LevelIndex])

	UE_LOG(LogTemp, Warning, TEXT("Float was = %f"),f_Seconds)
}


void USpheroidGameInstance::SaveLevelTimesToDisk()
{
		USpheroidSaveGame* SaveObject = Cast<USpheroidSaveGame>(UGameplayStatics::CreateSaveGameObject(USpheroidSaveGame::StaticClass()));

		for (int i = 0; i < NumberOfLevels; ++i)
		{
			*SaveObject->LevelTimes[i] = LevelTimes[i];
			*SaveObject->LevelsLocked[i] = LevelsLocked[i];
		}

		UGameplayStatics::SaveGameToSlot(SaveObject, SlotName, UserIndex);
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

					BreakTime(LevelTimes[i], i);
				}
			}
		}
	}
}