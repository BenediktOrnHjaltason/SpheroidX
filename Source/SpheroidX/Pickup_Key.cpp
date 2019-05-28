// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup_Key.h"
#include "Kismet/KismetMathLibrary.h"

APickup_Key::APickup_Key()
{

}

void APickup_Key::BeginPlay()
{
	Super::BeginPlay();

	GrowerMID = EffectPlane->CreateDynamicMaterialInstance(0);

	SetActorTickInterval(2.f);
}

void APickup_Key::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TL_RuntimeEffect();

}

void APickup_Key::RuntimeEffect(float Grower, float MID_Opacity)
{
	GrowerScale = { UKismetMathLibrary::Lerp(0.5f, 1.3f, Grower),
		UKismetMathLibrary::Lerp(0.5f, 1.3f, Grower), 1.f };

	EffectPlane->SetRelativeScale3D(GrowerScale);

	GrowerMID->SetScalarParameterValue("Opacity", MID_Opacity);
}