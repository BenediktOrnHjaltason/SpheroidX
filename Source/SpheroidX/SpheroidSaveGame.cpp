﻿// copyright Benedikt Orn Hjaltason


#include "SpheroidSaveGame.h"

USpheroidSaveGame::USpheroidSaveGame()
{
	SaveSlotName = TEXT("SpheroidOne");
	UserIndex = 0;

	LevelTimes.Init(nullptr, 2);
	LevelsLocked.Init(nullptr, 2);

	LevelTimes[0] = &time_L1;
	LevelTimes[1] = &time_L2;

	LevelsLocked[0] = &Locked_L1;
	LevelsLocked[1] = &Locked_L2;
}