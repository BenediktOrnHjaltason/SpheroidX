// Fill out your copyright notice in the Description page of Project Settings.


#include "SpheroidXGameModeBase.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"

void ASpheroidXGameModeBase::BeginPlay()
{
	Spheroid = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}