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
#include "Avatar.generated.h"

UCLASS()
class SPHEROIDX_API AAvatar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAvatar();
	
	UPROPERTY(EditAnywhere)
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

	FVector EntranceAttachLoc{ 0,0,0 };
	FVector ExitAttachLoc{ 0,0,0 };

	UWorld* CurrentWorld;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thrust)
		float BaseThrustStrength;

		float PickupMultiplier = 1;

		float InputMultiplier;

		float DegreesXRotation;


		float SpheroidXValue;
		float SpheroidYValue;

		void SpheroidXAxis(float AxisValue);

		void SpheroidYAxis(float AxisValue);

		//------------STATS-----------//
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Keys = 0;

		void IncrementKeys();
		//------------/STATS-----------//
		

		//----------POWERS------------//

		void StopMomentum();

		//----------/POWERS------------//

		//----------EFFECT_PLANE------//

		FLinearColor DeathColor{ 1.0f, 0.f, 0.f };
		FLinearColor BoostColor{0.f, 0.3836554f, 0.7791665f };

		FVector FrontPosition{ -1.f, 0.f, 0.f };
		FVector BackPosition{ 1.f, 0.f, 0.f };

		FVector Small{ 0.4f, 0.4, 1.f };
		FVector Big{ 2.f, 2.f, 1.f };

		UFUNCTION(BlueprintImplementableEvent)
			void TL_DeathEffect();

		UFUNCTION(BlueprintCallable)
			void DeathEffect(float TimelineScale);

		UFUNCTION(BlueprintCallable)
			void DeathEffectCleanUp();


		//----------/EFFECT_PLANE------//
		UFUNCTION()
			void Overlaps(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
				UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

		//------------DEATH-----------//
		void DeathSequence();

		UFUNCTION(BlueprintImplementableEvent)
			void TL_MoveToEntrance();

		UFUNCTION(BlueprintCallable)
			void MoveToEntrance(float Timeline);

		UFUNCTION(BlueprintCallable)
			void AfterMove();


		FVector DeathLocation;

		FTimerHandle MoveToEntranceHandle;

		//------------DEATH-----------//
				
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
