// copyright Benedikt Orn Hjaltason


#include "SpheroidSaveGame.h"

USpheroidSaveGame::USpheroidSaveGame()
{
	SaveSlotName = TEXT("SpheroidOne");
	UserIndex = 0;

	int NumberOfLevels = 6;

	LevelTimes.Init(nullptr, NumberOfLevels);
	LevelsLocked.Init(nullptr, NumberOfLevels);

	LevelTimes[0] = &time_L1;
	LevelTimes[1] = &time_L2;
	LevelTimes[2] = &time_L3;
	LevelTimes[3] = &time_L4;
	LevelTimes[4] = &time_L5;
	LevelTimes[5] = &time_L6;

	LevelsLocked[0] = &Locked_L1;
	LevelsLocked[1] = &Locked_L2;
	LevelsLocked[2] = &Locked_L3;
	LevelsLocked[3] = &Locked_L4;
	LevelsLocked[4] = &Locked_L5;
	LevelsLocked[5] = &Locked_L6;
}