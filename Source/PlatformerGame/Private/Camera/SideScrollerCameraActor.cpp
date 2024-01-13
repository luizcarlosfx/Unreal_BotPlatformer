// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/SideScrollerCameraActor.h"

#include "Camera/CameraComponent.h"
#include "Characters/BotCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraConfigTrigger.h"
#include "Components/SphereComponent.h"

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

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereCollision->SetupAttachment(GetRootComponent());

	// update after everything, like unity LateUpdate
	SetTickGroup(TG_PostUpdateWork);
}

void ASideScrollerCameraActor::BeginPlay()
{
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ASideScrollerCameraActor::OnOverlapBegin);
	Super::BeginPlay();
	bIsFirstFrame = true;
}

void ASideScrollerCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Target)
		return;

	if (bIsFirstFrame)
		InitializeTriggers();

	CalculateGoalLocation();
	UpdateCameraLocation(DeltaTime);
}

void ASideScrollerCameraActor::Setup(APlayerController* PlayerController, ABotCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	Target = TargetCharacter->GetCameraTarget();
	Controller = PlayerController;
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
		SetGoalX(CameraLocation.X);
		SetGoalZ(CameraLocation.Z);

		ActorLocation.Z = GoalZ;
		ActorLocation.X = GoalX;

		SetActorLocation(ActorLocation);
		bIsFirstFrame = false;
		return;
	}

	const bool bIsOutsideDeadZoneX = DeltaX > DeadZone.X;
	const bool bIsOutsideDeadZoneY = DeltaY > DeadZone.Y;

	bIsOutsideSoftZoneX = FMath::Abs(TargetScreenPos.X - 0.5f) > SoftZone.X * 0.5f;
	bIsOutsideSoftZoneY = FMath::Abs(TargetScreenPos.Y - 0.5f) > SoftZone.Y * 0.5f;

	if (bIsOutsideDeadZoneX || bIsOutsideSoftZoneX)
		SetGoalX(CameraLocation.X);

	if (bIsOutsideDeadZoneY || bIsOutsideSoftZoneY)
		SetGoalZ(CameraLocation.Z);
}

void ASideScrollerCameraActor::UpdateCameraLocation(const float& DeltaTime)
{
	FVector CameraLocation = GetActorLocation();

	float XSpeed = InterpolationSpeed.X;
	if (bIsOutsideSoftZoneX)
		XSpeed *= 2;

	float YSpeed = InterpolationSpeed.Y;
	if (bIsOutsideSoftZoneY)
		YSpeed *= 2;

	CameraLocation.X = FMath::FInterpTo(CameraLocation.X, GoalX, DeltaTime, XSpeed);
	CameraLocation.Z = FMath::FInterpTo(CameraLocation.Z, GoalZ, DeltaTime, YSpeed);

	SetActorLocation(CameraLocation);
}

void ASideScrollerCameraActor::SetGoalX(const float& value)
{
	GoalX = value;

	if (Bounds.UseMinX && GoalX < Bounds.MinX)
		GoalX = Bounds.MinX;

	if (Bounds.UseMaxX && GoalX > Bounds.MaxX)
		GoalX = Bounds.MaxX;
}

void ASideScrollerCameraActor::SetGoalZ(const float& value)
{
	GoalZ = value;

	if (Bounds.UseMinZ && GoalZ < Bounds.MinZ)
		GoalZ = Bounds.MinZ;

	if (Bounds.UseMaxZ && GoalZ > Bounds.MaxZ)
		GoalZ = Bounds.MaxZ;
}

void ASideScrollerCameraActor::InitializeTriggers()
{
	TArray<AActor*> Triggers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraConfigTrigger::StaticClass(), Triggers);

	for (AActor* Actor : Triggers)
	{
		const ACameraConfigTrigger* Trigger = Cast<ACameraConfigTrigger>(Actor);
		if (SphereCollision->IsOverlappingActor(Trigger))
			SetTrigger(Trigger);
		else
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("dAMN,,,,,,"));
	}
}

void ASideScrollerCameraActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                              bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Tags.Contains(ACameraConfigTrigger::Tag))
	{
		if (const ACameraConfigTrigger* Trigger = Cast<ACameraConfigTrigger>(OtherActor))
			SetTrigger(Trigger);
	}
}

void ASideScrollerCameraActor::SetTrigger(const ACameraConfigTrigger* Trigger)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, Trigger->GetActorLabel());
	Bounds = Trigger->GetCameraBounds();
}
