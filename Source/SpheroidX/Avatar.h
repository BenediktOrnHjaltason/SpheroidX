// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
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

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPhysicsThrusterComponent* Thruster;
	
	void ThrustOn();

	void ThrustOff();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
