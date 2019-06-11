// copyright Benedikt Örn Hjaltason


#include "SpheroidGameInstance.h"


/*
GameInstance holds HighScore times

*/

USpheroidGameInstance::USpheroidGameInstance()
{
	int NumberOfLevels = 2;

	LevelTimes.Init(0.f, NumberOfLevels);
	LevelTimesMinutes.Init(0, NumberOfLevels);
	LevelTimesSeconds.Init(0, NumberOfLevels);
	LevelTimesRemaining.Init(0, NumberOfLevels);
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
	UE_LOG(LogTemp, Warning, TEXT("SaveLevelTimeToDisk called"))
	USpheroidSaveGame* TempSaveObject = Cast<USpheroidSaveGame>(UGameplayStatics::CreateSaveGameObject(USpheroidSaveGame::StaticClass()));
	TempSaveObject->time_L1 = LevelTimes[0];
	
	UGameplayStatics::SaveGameToSlot(TempSaveObject, TempSaveObject->SaveSlotName, TempSaveObject->UserIndex);
}

void USpheroidGameInstance::LoadLevelTimesFromDisk()
{
	UE_LOG(LogTemp, Warning, TEXT("LoadLevelTimesToDisk called"))
	SaveObject = Cast<USpheroidSaveGame>(UGameplayStatics::CreateSaveGameObject(USpheroidSaveGame::StaticClass()));
	SaveObject = Cast<USpheroidSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveObject->SaveSlotName, SaveObject->UserIndex));
	LevelTimes[0] = SaveObject->time_L1;
	
	BreakTime(LevelTimes[0], LevelTimesMinutes[0], LevelTimesSeconds[0], LevelTimesRemaining[0]);

	UE_LOG(LogTemp, Warning, TEXT("GameInstance: LoadLevelTimesFromDisk called. SaveObject L1_time: %f, GI_LevelTimes[0]: %f"), SaveObject->time_L1, LevelTimes[0])
	
}