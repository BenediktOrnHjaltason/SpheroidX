// copyright Benedikt Orn Hjaltason


#include "SpheroidSaveGame.h"

USpheroidSaveGame::USpheroidSaveGame()
{
	SaveSlotName = TEXT("SpheroidOne");
	UserIndex = 0;


	LevelTimes.Init(nullptr, NumberOfLevels);
	LevelsLocked.Init(nullptr, NumberOfLevels);

	LevelTimes[0] = &time_L1;
	LevelTimes[1] = &time_L2;
	LevelTimes[2] = &time_L3;
	LevelTimes[3] = &time_L4;
	LevelTimes[4] = &time_L5;
	LevelTimes[5] = &time_L6;
	LevelTimes[6] = &time_L7;
	LevelTimes[7] = &time_L8;
	LevelTimes[8] = &time_L9;
	LevelTimes[9] = &time_L10;
	LevelTimes[10] = &time_L11;
	LevelTimes[11] = &time_L12;
	LevelTimes[12] = &time_L13;
	LevelTimes[13] = &time_L14;
	LevelTimes[14] = &time_L15;
	LevelTimes[15] = &time_L16;
	LevelTimes[16] = &time_L17;
	LevelTimes[17] = &time_L18;
	LevelTimes[18] = &time_L19;
	LevelTimes[19] = &time_L20;
	LevelTimes[20] = &time_L21;
	LevelTimes[21] = &time_L22;
	LevelTimes[22] = &time_L23;
	LevelTimes[23] = &time_L24;

	LevelsLocked[0] = &Locked_L1;
	LevelsLocked[1] = &Locked_L2;
	LevelsLocked[2] = &Locked_L3;
	LevelsLocked[3] = &Locked_L4;
	LevelsLocked[4] = &Locked_L5;
	LevelsLocked[5] = &Locked_L6;
	LevelsLocked[6] = &Locked_L7;
	LevelsLocked[7] = &Locked_L8;
	LevelsLocked[8] = &Locked_L9;
	LevelsLocked[9] = &Locked_L10;
	LevelsLocked[10] = &Locked_L11;
	LevelsLocked[11] = &Locked_L12;
	LevelsLocked[12] = &Locked_L13;
	LevelsLocked[13] = &Locked_L14;
	LevelsLocked[14] = &Locked_L15;
	LevelsLocked[15] = &Locked_L16;
	LevelsLocked[16] = &Locked_L17;
	LevelsLocked[17] = &Locked_L18;
	LevelsLocked[18] = &Locked_L19;
	LevelsLocked[19] = &Locked_L20;
	LevelsLocked[20] = &Locked_L21;
	LevelsLocked[21] = &Locked_L22;
	LevelsLocked[22] = &Locked_L23;
	LevelsLocked[23] = &Locked_L24;
}