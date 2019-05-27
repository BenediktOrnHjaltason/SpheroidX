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
	Exit				UMETA(DisplayName = "Exit")
};

UENUM(BlueprintType)
enum class EOpenOrClose : uint8
{
	Open				UMETA(DisplayName = "Open"),
	Close				UMETA(DisplayName = "Close")
};

UCLASS()
class SPHEROIDX_API UMyEnums : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};
