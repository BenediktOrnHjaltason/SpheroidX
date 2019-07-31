// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "Kismet/KismetMathLibrary.h"
#include "LevelTransitionDevice.h"
#include "SpheroidXGameModeBase.h"
#include "EngineUtils.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "SpheroidGameInstance.h"
#include "Portal.h"

// Sets default values
AAvatar::AAvatar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Image Plane"));
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	Thruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("Thruster"));
	Exhaust = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Exhaust"));
	EffectPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EffectPlane"));

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));

	RootComponent = Collision;

	Collision->SetSphereRadius(32);
	
	PlaneMesh->SetupAttachment(Collision);
	Thruster->SetupAttachment(Collision);
	SpringArm->SetupAttachment(Collision);
	Camera->SetupAttachment(SpringArm);
	Exhaust->SetupAttachment(Collision);
	EffectPlane->SetupAttachment(Collision);
	AudioComp->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{

	Super::BeginPlay();

	CurrentWorld = GetWorld();
	GameModeRef = Cast<ASpheroidXGameModeBase>(GetWorld()->GetAuthGameMode());
	GameInstance = Cast<USpheroidGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	ExhaustMID = Exhaust->CreateDynamicMaterialInstance(0);
	//EffectMID = EffectPlane->CreateDynamicMaterialInstance(0);

	SetActorTickEnabled(false);
	Exhaust->SetVisibility(false);

	MaterialParameters = LoadObject<UMaterialParameterCollection>(NULL, TEXT("MaterialParameterCollection'/Game/Materials/MaterialParameterCollection_Spheroid.MaterialParameterCollection_Spheroid'"),
		NULL, LOAD_None, NULL);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AAvatar::Overlaps);

	for (TActorIterator<ALevelTransitionDevice> DeviceItr(GetWorld()); DeviceItr; ++DeviceItr)
	{
		ALevelTransitionDevice *Device = *DeviceItr;
		if (Device->EntranceOrExit == ELTD_Type::Exit || Device->EntranceOrExit == ELTD_Type::TutorialExit)
		{
			LevelExit = Device;
			ExitAttachLoc = LevelExit->PawnAttachLocation->GetComponentLocation();
		}
		else if (Device->EntranceOrExit == ELTD_Type::Entrance)
		{
			LevelEntrance = Device;
			EntranceAttachLoc = LevelEntrance->PawnAttachLocation->GetComponentLocation();
		}
	}

	LevelPortal = CurrentWorld->SpawnActor<APortal>(PortalToSpawn, GetActorLocation(), FRotator(0));

	AudioComp->Play();
}

// Called every frame
void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InputMultiplier = UKismetMathLibrary::Sqrt(
		UKismetMathLibrary::MultiplyMultiply_FloatFloat(SpheroidXValue, 2)
		+ UKismetMathLibrary::MultiplyMultiply_FloatFloat(SpheroidYValue, 2));

	if (InputMultiplier > 1) InputMultiplier = 1;
	
	Thruster->ThrustStrength = InputMultiplier * BaseThrustStrength;

	if (InputMultiplier > 0.05)
		SetActorRotation(FRotator(0.f, 0.f, UKismetMathLibrary::DegAtan2(SpheroidXValue, SpheroidYValue)));

	
	ExhaustMID->SetScalarParameterValue("Opacity", InputMultiplier);
	Exhaust->SetRelativeScale3D(FVector(0.5f, UKismetMathLibrary::Lerp(0.5f, 1.0f, InputMultiplier), 1));

	AudioComp->SetVolumeMultiplier(InputMultiplier);

}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("SpheroidX", this, &AAvatar::SpheroidXAxis);
	PlayerInputComponent->BindAxis("SpheroidY", this, &AAvatar::SpheroidYAxis);
	PlayerInputComponent->BindAction("StopMomentum", IE_Pressed, this, &AAvatar::StopMomentum);
	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &AAvatar::BoostProxy);
	PlayerInputComponent->BindAction("Portal", IE_Pressed, this, &AAvatar::UsePortal);
	PlayerInputComponent->BindAction("MoveCamera", IE_Pressed, this, &AAvatar::MoveCamera);
}

void AAvatar::SpheroidXAxis(float AxisValue)
{
	SpheroidXValue = AxisValue;
}

void AAvatar::SpheroidYAxis(float AxisValue)
{
	SpheroidYValue = AxisValue;
}

void AAvatar::IncrementKeys()
{
	++Keys;

	if (LevelExit->EntranceOrExit != ELTD_Type::TutorialExit && Keys >= LevelExit->KeysNeededToOpen && LevelExit->KeysNeededToOpen != 0)
	{
		LevelExit->TL_OperateDoors(EOpenOrClose::Open, false, true);
	}
}

void AAvatar::Overlaps(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
		if (OtherActor->IsA(ALevelTransitionDevice::StaticClass()) && 
			Cast<ALevelTransitionDevice>(OtherActor)->EntranceOrExit == ELTD_Type::Exit)
		{
			CalculateTime(GameInstance->LevelIndex);

			DisplayTime();

			//Reset for next round
			GameInstance->OldTimeForComparison = 0.f;

			//unlock next level if there is next level
			if (GameInstance->LevelsLocked.IsValidIndex(GameInstance->LevelIndex + 1))
				GameInstance->LevelsLocked[GameInstance->LevelIndex + 1] = false;

			if (GameInstance->LevelIndex == 47)
			{
				GameInstance->bHasPlayerWonTheGame = true;
				CreateWinScreen();
			}
		}

	else if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic || OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_GameTraceChannel2)
	{
			
		UKismetMaterialLibrary::SetVectorParameterValue(CurrentWorld, MaterialParameters, "Effect_Color", DeathColor);

		if (LevelExit->EntranceOrExit != ELTD_Type::TutorialExit && Keys >= LevelExit->KeysNeededToOpen) LevelExit->DeactivateExit();


		if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_GameTraceChannel2)
		{
			BlackHoleLocation = OtherActor->GetActorLocation();		
			DeathSequence(true);
		}

		else DeathSequence();

		bIsDeathSequenceRunning = true;
	}
}

// DeathLocation is set to blackhole location to have correct movement back to LTD,
// but this causes movementlerping to have no effect

void AAvatar::CalculateTime(int LevelIndex)
{
	GameInstance->CurrentTimeSeconds = CurrentWorld->GetRealTimeSeconds() - TimeAtShootOut;

	GameInstance->CurrentTimesMilliSeconds = GameInstance->CurrentTimeSeconds * 1000;

	GameInstance->HandleLeaderboard(GameInstance->CurrentTimesMilliSeconds);

	GameInstance->BreakTimeLevelEnd(GameInstance->CurrentTimeSeconds, GameInstance->LevelIndex);

	if (GameInstance->GetLevelTime() == 0 || GameInstance->CurrentTimeSeconds < GameInstance->GetLevelTime())
	{
		GameInstance->ManageNewHighScore(GameInstance->CurrentTimeSeconds);
	}
}

void AAvatar::DeathSequence(bool bDeathByBlackHole)
{	
	if (bIsTravelingThroughPortal) return;

	SetActorTickEnabled(false);
	AudioComp->SetVolumeMultiplier(0.f);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);

	UKismetMaterialLibrary::SetScalarParameterValue(CurrentWorld, MaterialParameters, "Effect_Opacity", 1);

	DeathLocation = GetActorLocation();

	if (bDeathByBlackHole)
	{
		EffectPlane->SetVisibility(false);
		TL_DeathEffect(true, DeathLocation, BlackHoleLocation);
	}

	else
	{
		PlaneMesh->SetVisibility(false);
		TL_DeathEffect();
	}

	Collision->SetLinearDamping(1000);
	Collision->SetAllPhysicsLinearVelocity(FVector(0, 0, 0));
	
	Exhaust->SetVisibility(false);
	
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);

	GameModeRef->NotifiedOfDeath();

	if (!GameModeRef->bIsTutorialLevel)
	{
		GameModeRef->ResetPickups();
		LevelExit->SpheroidKeyCount = 0;
	}

	if (LevelPortal->bIsPortalActive)
	{
		ResetPortalOnDeath();
	}


	bIsFirstTimeOnLevel = false;
	bIsEffectAllowed = false;

	Keys = 0;

	GetWorldTimerManager().SetTimer(MoveToEntranceHandle, this, &AAvatar::TL_MoveToEntrance, 1.25f, false);
}

void AAvatar::MoveToEntrance(float Timeline)
{
	SetActorLocation(UKismetMathLibrary::VLerp(DeathLocation, EntranceAttachLoc, Timeline));
}

void AAvatar::AfterMove()
{
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Overlap);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Overlap);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);
	LevelEntrance->TL_OperateDoors(EOpenOrClose::Close, true);
}

void AAvatar::AfterBlackHoleShrink()
{
	DeathLocation = FVector(GetActorLocation().X, BlackHoleLocation.Y, BlackHoleLocation.Z);
}


void AAvatar::DeathEffect(float TimelineScale)
{
	EffectPlane->SetRelativeScale3D(UKismetMathLibrary::VLerp(Small, DeathBig, TimelineScale));
}

void AAvatar::EffectCleanUp()
{
	UKismetMaterialLibrary::SetScalarParameterValue(CurrentWorld, MaterialParameters, "Effect_Opacity", 0);
	EffectPlane->SetRelativeScale3D(Small);
	bIsEffectAllowed = true;
}

void AAvatar::BoostProxy()
{
	if (bIsDeathSequenceRunning) return;

	Collision->SetPhysicsLinearVelocity(FVector(0.f, 0.f, 0.f));

	Collision->AddImpulse(GetActorUpVector() * 10000);
	UGameplayStatics::PlaySound2D(CurrentWorld, BoostSound, 1.f, 1.f, 0.15f);
	TL_BoostEffect();
	
}

void AAvatar::BoostEffect(float TimelineScale, float TimelineOpacity)
{

	EffectPlane->SetRelativeScale3D(UKismetMathLibrary::VLerp(Small, BoostBig, TimelineScale));
	UKismetMaterialLibrary::SetScalarParameterValue(CurrentWorld, MaterialParameters, "Effect_Opacity", TimelineOpacity);

}

void AAvatar::StopMomentum()
{
	Collision->SetPhysicsLinearVelocity(FVector(0, 0, 0));

	if (bIsDeathSequenceRunning) return;

	UKismetMaterialLibrary::SetVectorParameterValue(CurrentWorld, MaterialParameters, "Effect_Color", BoostColor);
	UKismetMaterialLibrary::SetScalarParameterValue(CurrentWorld, MaterialParameters, "Effect_Opacity", 1);
	UGameplayStatics::PlaySound2D(CurrentWorld, StopMomentumSound);
	TL_StopMomentumEffect();
}

void AAvatar::StopMomentumEffect(float TimelineScale)
{
	EffectPlane->SetRelativeScale3D(UKismetMathLibrary::VLerp(BoostBig, Small, TimelineScale));
}


void AAvatar::UsePortal()
{
	if (bIsDeathSequenceRunning) return;

	//True for travel through, false for make
	bMakeOrTravel = !bMakeOrTravel;

	if (bMakeOrTravel)
	{
		if (bIsTravelingThroughPortal)
		{
			bMakeOrTravel = !bMakeOrTravel;
			return;
		}
		Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);
		Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
		bIsTravelingThroughPortal = true;
		Exhaust->SetVisibility(false);
		EffectPlane->SetVisibility(false);
		PortalMorph();
		GetWorldTimerManager().SetTimer(PortalDisappearTimer, this, &AAvatar::TravelPortalTimerProxy, 0.25f, false);
		bShouldChangeButtonImage = true;
		GameModeRef->ChangePortalButtonIcon(false);
	}

	else
	{
		if (bIsTravelingThroughPortal || LevelPortal->bIsPortalActive)
		{
			bMakeOrTravel = !bMakeOrTravel;
			return;
		}

		LevelPortal->bIsPortalActive = true;
		LevelPortal->SetActorLocation(GetActorLocation() + SpawnOffsett);

		LevelPortal->Morph(EOpenOrClose::Open);
		bShouldChangeButtonImage = true;
		GameModeRef->ChangePortalButtonIcon(false);
	}
}

void AAvatar::TravelPortalTimerProxy()
{
		SetActorLocation(LevelPortal->GetActorLocation() - SpawnOffsett);
		GetWorldTimerManager().SetTimer(PortalDisappearTimer, this, &AAvatar::PortalDissapear, 1.f, false);
}

void AAvatar::PortalMorphCleanUp()
{
	Exhaust->SetVisibility(true);
	EffectPlane->SetVisibility(true);
	bIsTravelingThroughPortal = false;
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);
}

void AAvatar::PortalDissapear()
{
	LevelPortal->Morph(EOpenOrClose::Close);
}

void AAvatar::MoveCamera()
{
	bCameraSwitchBool = !bCameraSwitchBool;

	if (bCameraSwitchBool) Camera->SetRelativeLocation(CameraLowerPosition);

	else Camera->SetRelativeLocation(CameraUpperPosition);
}

void AAvatar::ResetPortalOnDeath()
{
	LevelPortal->bIsPortalActive = false;
	bIsTravelingThroughPortal = false;
	bMakeOrTravel = true;
	LevelPortal->SetActorHiddenInGame(true);
	GameModeRef->ChangePortalButtonIcon(true);
}