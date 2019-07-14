// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/StaticMeshActor.h"
#include "TimerManager.h"
#include "Materials/MaterialParameterCollection.h"
#include "Components/AudioComponent.h"
#include "MyEnums.h"
#include "Avatar.generated.h"

UCLASS()
class SPHEROIDX_API AAvatar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAvatar();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* PlaneMesh;

	UPROPERTY(VisibleAnywhere)
		USphereComponent* Collision;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPhysicsThrusterComponent* Thruster;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Exhaust;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* EffectPlane;

	UMaterialInstanceDynamic* ExhaustMID;
	UMaterialInstanceDynamic* EffectMID;

	UMaterialParameterCollection* MaterialParameters;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ALevelTransitionDevice* LevelExit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ALevelTransitionDevice* LevelEntrance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ASpheroidXGameModeBase* GameModeRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EntranceAttachLoc{ 0,0,0 };

	UPROPERTY(EditAnywhere)
		UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundBase* BoostSound;

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundBase* StopMomentumSound;

	FVector ExitAttachLoc{ 0,0,0 };

	UWorld* CurrentWorld;

	class USpheroidGameInstance* GameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thrust)
		float BaseThrustStrength;

		float PickupMultiplier = 1;

		float InputMultiplier;

		float DegreesXRotation;


		float SpheroidXValue;
		float SpheroidYValue;

		void SpheroidXAxis(float AxisValue);

		void SpheroidYAxis(float AxisValue);

		bool bIsFirstTimeOnLevel = true;

		//------------Camera Movement-//

		float ZVelocity = 0.f;

		FVector CameraUpperPosition{ 0.f, 0.f, 130.f };
		FVector CameraLowerPosition{ 0.f, 0.f, -100.f };
		//FVector LocationAtDirectionChange{ 0.f, 0.f, 0.f };

		bool bIsMovingUp = false;
		bool bIsMovingDown = false;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bShouldCameraStartMoving = true;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			bool bChangedDirection = false;

		UFUNCTION(BlueprintImplementableEvent)
			void LerpCamera(FVector LocationAtDirectionChange, FVector TowardsPosition);



		//------------STATS-----------//
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Keys = 0;

		void IncrementKeys();

		UFUNCTION(BlueprintImplementableEvent)
			void FadeWidgetInOut();
		//------------/STATS-----------//

		//-------------TIME------------//
		float TimeAtShootOut;


		UFUNCTION(BlueprintImplementableEvent)
			void DisplayTime();

		void CalculateTime(int LevelIndex);

		//------------/TIME------------//
		

		//-------Level Management------//
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName PreviousLevel;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName CurrentLevel;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName NextLevel;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bIsFirstLevel = false;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bIsTutorialLevel = false;



		//-------/Level Management-----//

		//----------POWERS------------//

		

		//----------/POWERS------------//

		//----------EFFECT_PLANE------//

		FVector Small{ 0.4f, 0.4, 1.f };

		//Death
		FLinearColor DeathColor{ 1.0f, 0.f, 0.f };
		
		FVector DeathBig{ 2.f, 2.f, 1.f };

		UFUNCTION(BlueprintImplementableEvent)
			void TL_DeathEffect();

		UFUNCTION(BlueprintCallable)
			void DeathEffect(float TimelineScale);

		UFUNCTION(BlueprintCallable)
			void EffectCleanUp();

		//Boost

		FVector BoostBig{ 2.f, 2.f, 1.f };

		FLinearColor BoostColor{ 0.f, 0.3836554f, 0.7791665f };


		UFUNCTION(BlueprintImplementableEvent)
			void TL_BoostEffect();

		UFUNCTION(BlueprintCallable)
			void BoostEffect(float TimelineScale, float TimelineOpacity);

		UFUNCTION(BlueprintCallable)
		void BoostProxy();

		bool bIsEffectAllowed = false;

		bool bIsDeathSequenceRunning = false;

		//Stop momentum

		UFUNCTION(BlueprintImplementableEvent)
			void TL_StopMomentumEffect();

		UFUNCTION(BlueprintCallable)
			void StopMomentumEffect(float TimelineScale);

		UFUNCTION(BlueprintCallable)
		void StopMomentum();

		//----------/EFFECT_PLANE------//
		UFUNCTION()
			void Overlaps(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
				UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

		//------------DEATH-----------//
		UFUNCTION(BlueprintCallable)
		void DeathSequence();

		UFUNCTION(BlueprintImplementableEvent)
			void TL_MoveToEntrance();

		UFUNCTION(BlueprintCallable)
			void MoveToEntrance(float Timeline);

		UFUNCTION(BlueprintCallable)
			void AfterMove();


		FVector DeathLocation;

		FTimerHandle MoveToEntranceHandle;

		//------------/DEATH-----------//

		//------------Portal-----------//

		class APortal* LevelPortal;

		UPROPERTY(EditAnywhere)
		TSubclassOf<class APortal> PortalToSpawn;

		//False for make, true for travel
		bool bMakeOrTravel = true;

		FVector SpawnOffsett{ 5.f, 0.f, 0.f };

		UFUNCTION(BlueprintCallable)
		void UsePortal();

		void TravelPortalTimerProxy();

		FTimerHandle PortalMorphTimer;

		UFUNCTION(BlueprintImplementableEvent)
			void PortalMorph();

		UFUNCTION(BlueprintCallable)
			void PortalMorphCleanUp();

		FTimerHandle PortalDisappearTimer;
		void PortalDissapear();

		//Used together with LevelPortal->bIsAcive
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsTravelingThroughPortal = false;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			bool bShouldChangeButtonImage = false;

		void ResetPortalOnDeath();

		//------------/Portal-----------//

		//--------Move Camera-----------//

		UFUNCTION(BlueprintCallable)
			void MoveCamera();

		bool bCameraSwitchBool = false;
		//-------/Move Camera-----------//

		


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
