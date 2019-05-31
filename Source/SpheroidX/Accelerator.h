// © copyright Benedikt Örn Hjaltason

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Accelerator.generated.h"

UCLASS()
class SPHEROIDX_API AAccelerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAccelerator();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* Collision;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	class AAvatar* Spheroid;

	UWorld* CurrentWorld;

	UPROPERTY(EditAnywhere, Category = Sound)
	USoundBase* AcceleratorEffect;

	UPROPERTY(EditAnywhere)
	float Accelleration;

	UFUNCTION()
		void Overlaps(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
			UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
