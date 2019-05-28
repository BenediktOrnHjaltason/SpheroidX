// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyEnums.h"
#include "TimerManager.h"
#include "LevelTransitionDevice.generated.h"

UCLASS()
class SPHEROIDX_API ALevelTransitionDevice : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelTransitionDevice();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* Collision;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Base;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* LeftDoor;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* RightDoor;

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundBase* Open;

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundBase* Thonk;

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundBase* ReceiveSpheroid;

	UPROPERTY(EditAnywhere, Category = LevelTransitionDevice)
		ELTD_Type EntranceOrExit;

	UPROPERTY(EditAnywhere)
		USceneComponent* PawnAttachLocation;

	class AAvatar* Spheroid;

	//START Doors

	UFUNCTION(BlueprintImplementableEvent)
		void TL_OperateDoors(EOpenOrClose OpenOrClose);

	UFUNCTION(BlueprintCallable)
		void OperateDoors(EOpenOrClose OpenOrClose, float Timeline);


	FRotator LeftDoorClosed{ 0.f, 450.f, 450.f };
	FRotator LeftDoorOpen{ 35.f, 450.f, 450.f };

	FRotator RightDoorClosed{ 0.f, 810.f, 90.f };
	FRotator RightDoorOpen{ -35.f, 810.f, 90.f };
	//END Doors

	FTimerHandle StartImpulseTimer;
	FTimerHandle EnableSpheroidInputTimer;

	void ShootOutSpheroid();
	void ReactivateSpheroidInput();

	UPROPERTY(EditAnywhere, Category = Stats)
		int KeysNeededToOpen;

	UFUNCTION()
		void CatchSpheroid(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
			UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
