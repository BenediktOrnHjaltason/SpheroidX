// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyEnums.h"
#include "TimerManager.h"
#include "Materials/MaterialParameterCollection.h"
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

	UWorld* CurrentWorld;
	
	UMaterialParameterCollection* MaterialParameters;


	//--------BlinkingLights-----------//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* BlinkingLight;

	FVector RedLight{ 1.f, 0.f, 0.f };
	FVector GreenLight{ 0.f, 1.f, 0.f };

	bool DummyBool = false;

	UFUNCTION(BlueprintCallable)
		void SetLightToGreen();

	void DeactivateExit();



	//--------/BlinkingLights-----------//

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundBase* Open;

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundBase* Thonk;

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundBase* ReceiveSpheroid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = LevelTransitionDevice)
		ELTD_Type EntranceOrExit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USceneComponent* PawnAttachLocation;

	class AAvatar* Spheroid;

	class ASpheroidXGameModeBase* GameModeRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int SpheroidKeyCount = 0;

	


	//START Doors

	UFUNCTION(BlueprintImplementableEvent)
		void TL_OperateDoors(EOpenOrClose OpenOrClose, bool ForRespawn = false, bool bForExitUnlock = false);

	UFUNCTION(BlueprintCallable)
		void OperateDoors(EOpenOrClose OpenOrClose, float Timeline);


	FRotator LeftDoorClosed{ 0.f, 450.f, 450.f };
	FRotator LeftDoorOpen{ 35.f, 450.f, 450.f };

	FRotator RightDoorClosed{ 0.f, 810.f, 90.f };
	FRotator RightDoorOpen{ -35.f, 810.f, 90.f };
	//END Doors

	UPROPERTY(EditAnywhere)
	USoundBase* Sound_ReachedGoal;

	FTimerHandle StartImpulseTimer;
	FTimerHandle EnableSpheroidInputTimer;
	FTimerHandle ShootOutSequenceTimer;

	UFUNCTION(BlueprintCallable)
	void PrepareSpheroidForLaunch();

	UFUNCTION(BlueprintCallable)
	void ShootOutSequence();
	
	UFUNCTION(BlueprintCallable)
	void ShootOutSpheroid();

	void ReactivateSpheroidInput();

	//HUD is created here and simultaneaously gives gamemode a reference to it
	UFUNCTION(BlueprintImplementableEvent)
		void CreateHUD(bool bIsTutorialLevel = true);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
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
