// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/SideScrollerCameraActor.h"

#include "Camera/CameraComponent.h"
#include "Characters/BotCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASideScrollerCameraActor::ASideScrollerCameraActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// update after everything, like unity LateUpdate
	SetTickGroup(TG_PostUpdateWork);
}

void ASideScrollerCameraActor::BeginPlay()
{
	Super::BeginPlay();
	bIsFirstFrame = true;
}

void ASideScrollerCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateGoalLocation();
	UpdateCameraLocation(DeltaTime);
}

void ASideScrollerCameraActor::Setup(ABotCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	Target = TargetCharacter->GetCameraTarget();
	Controller = Cast<APlayerController>(Character->GetController());
	Controller->SetViewTarget(this);
}

void ASideScrollerCameraActor::CalculateGoalLocation()
{
	const FVector& TargetLocation = Target->GetComponentLocation();

	// get screen size in pixels
	int32 ScreenSizeX, ScreenSizeY;
	Controller->GetViewportSize(ScreenSizeX, ScreenSizeY);

	// if the player is looking back then the target position in x has to be flipped too
	FVector2d DesiredScreenPos = DesiredScreenPosition;
	if (Character->IsFlipped())
		DesiredScreenPos.X = 1 - DesiredScreenPos.X;

	// get target position on screen space in pixels
	FVector2d TargetScreenPos;
	UGameplayStatics::ProjectWorldToScreen(Controller, TargetLocation, TargetScreenPos);

	// convert screen space pixels into a normalized position (0 to 1)
	TargetScreenPos.X /= ScreenSizeX;
	TargetScreenPos.Y = 1 - (TargetScreenPos.Y / ScreenSizeY);

	// calculate distance between the goal position and the target position on screen space
	const float DeltaX = FMath::Abs(DesiredScreenPos.X - TargetScreenPos.X);
	const float DeltaY = FMath::Abs(DesiredScreenPos.Y - TargetScreenPos.Y);

	// transform the target position normalized position into pixels
	DesiredScreenPos.X *= ScreenSizeX;
	DesiredScreenPos.Y = (1 - DesiredScreenPos.Y) * ScreenSizeY;

	// convert target position from screen space to world
	FVector TargetWorldPos, TargetWorldDirection;
	UGameplayStatics::DeprojectScreenToWorld(Controller, DesiredScreenPos, TargetWorldPos, TargetWorldDirection);

	// project world position into the 2d plane
	const FPlane Plane(FVector::Zero(), FVector::RightVector);
	const FVector DesiredLocation = FMath::RayPlaneIntersection(TargetWorldPos, TargetWorldDirection, Plane);

	// calculate camera location based on the distance between the target location and the desired location
	const FVector DeltaMove = TargetLocation - DesiredLocation;
	FVector ActorLocation = GetActorLocation();
	const FVector CameraLocation = ActorLocation + DeltaMove;

	// a little trick to move the camera immediately on the first frame
	if (bIsFirstFrame)
	{
		ActorLocation.X = GoalX = CameraLocation.X;
		ActorLocation.Z = GoalZ = CameraLocation.Z;

		SetActorLocation(ActorLocation);
		bIsFirstFrame = false;
		return;
	}

	const FVector& CharacterSpeed = Character->GetVelocity();
	const bool bCharacterMovingX = FMath::Abs(CharacterSpeed.X) > 0;
	const bool bCharacterMovingZ = FMath::Abs(CharacterSpeed.Z) > 0;

	const bool bIsOutsideDeadZoneX = DeltaX > DeadZone.X;
	const bool bIsOutsideDeadZoneY = DeltaY > DeadZone.Y;

	const bool bIsOutsideSoftZoneX = FMath::Abs(TargetScreenPos.X - 0.5f) > SoftZone.X * 0.5f;
	const bool bIsOutsideSoftZoneY = FMath::Abs(TargetScreenPos.Y - 0.5f) > SoftZone.Y * 0.5f;

	// move only if:
	// 1 - we are outside of the dead zone 
	// 2 - we were previously moving the camera and the character is moving
	// 3 - we are outside of the camera safe zone 
	if (bIsOutsideDeadZoneX || (bIsMovingX && bCharacterMovingX) || bIsOutsideSoftZoneX)
	{
		GoalX = CameraLocation.X;
		bIsMovingX = true;
	}
	else
	{
		bIsMovingX = false;
	}

	if (bIsOutsideDeadZoneY || (bIsMovingZ && bCharacterMovingZ) || bIsOutsideSoftZoneY)
	{
		GoalZ = CameraLocation.Z;
		bIsMovingZ = true;
	}
	else
	{
		bIsMovingZ = false;
	}
}

void ASideScrollerCameraActor::UpdateCameraLocation(const float& DeltaTime)
{
	FVector CameraLocation = GetActorLocation();
	CameraLocation.X = FMath::FInterpTo(CameraLocation.X, GoalX, DeltaTime, InterpolationSpeed.X);
	CameraLocation.Z = FMath::FInterpTo(CameraLocation.Z, GoalZ, DeltaTime, InterpolationSpeed.Y);
	
	SetActorLocation(CameraLocation);
}
