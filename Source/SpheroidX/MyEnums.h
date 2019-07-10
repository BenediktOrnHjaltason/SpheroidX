// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "MyEnums.generated.h"

/**
 * 
 */

//LTD = LevelTransitionDevice

UENUM(BlueprintType)
enum class ELTD_Type : uint8
{
	Entrance			UMETA(DisplayName = "Entrance"),
	Exit				UMETA(DisplayName = "Exit"),
	TutorialExit		UMETA(DisplayName = "Tutorial Exit")
};

UENUM(BlueprintType)
enum class EOpenOrClose : uint8
{
	Open				UMETA(DisplayName = "Open"),
	Close				UMETA(DisplayName = "Close")
};

UENUM(BlueprintType)
enum class EPickupType : uint8
{
	Key					UMETA(DisplayName = "Key"),
	Boost				UMETA(DisplayName = "Boost")
};

UCLASS()
class SPHEROIDX_API UMyEnums : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class EHUDAnimations : uint8
{
	CountDown			UMETA(DisplayName = "CountDown"),
	ReachedGoal			UMETA(DisplayName = "ReachedGoal"),
	RespawnGo			UMETA(DisplayName = "RespawnGo"),
	FadeInOutRemaining	UMETA(DisplayName = "FadeInOutRemaining")
};

UENUM(BlueprintType)
enum class ECameraShakes : uint8
{
	Death				UMETA(DisplayName = "Death"),
};

