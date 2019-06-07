// Fill out your copyright notice in the Description page of Project Settings.


#include "SpheroidXGameModeBase.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"

void ASpheroidXGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentWorld = GetWorld();

	Spheroid = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	MaterialParameters = LoadObject<UMaterialParameterCollection>(NULL, TEXT("MaterialParameterCollection'/Game/Materials/MaterialParameterCollection_Spheroid.MaterialParameterCollection_Spheroid'"),
		NULL, LOAD_None, NULL);
}

void ASpheroidXGameModeBase::Status_TurnToActive()
{
	UKismetMaterialLibrary::SetVectorParameterValue(CurrentWorld, MaterialParameters, "StatusSwitch", Status_Active);
}

void ASpheroidXGameModeBase::Status_TurnToInactive()
{
	UKismetMaterialLibrary::SetVectorParameterValue(CurrentWorld, MaterialParameters, "StatusSwitch", Status_Inactive);
}