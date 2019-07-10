// copyright Benedikt Orn Hjaltason

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "MyEnums.h"
#include "Portal.generated.h"

UCLASS()
class SPHEROIDX_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

	UPROPERTY(EditAnywhere)
	USceneComponent* SceneRoot;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PortalPlane1;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PortalPlane2;

	FRotator BaseRotateDelta{ 0.f, 0.f, 1.f };
	FRotator CenterRotateDelta{0.f, 0.f, -2.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPortalActive = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
		void Morph(EOpenOrClose OpenOrClose);

};
