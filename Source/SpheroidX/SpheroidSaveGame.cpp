// copyright Benedikt Örn Hjaltason


#include "SpheroidSaveGame.h"

USpheroidSaveGame::USpheroidSaveGame()
{
	UserIndex = 0;
	SaveSlotName = TEXT("Spheroid");

	//dummy float variable
	LevelTimes.Init(nullptr, 2);

	LevelTimes[0] = &time_L1;
	LevelTimes[1] = &time_L2;
}