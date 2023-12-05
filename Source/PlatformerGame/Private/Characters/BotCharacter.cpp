// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BotCharacter.h"

#include "FCTween.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/ThrowableActor.h"


// Sets default values
ABotCharacter::ABotCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bConstrainToPlane = true;
	Movement->SetPlaneConstraintNormal(FVector(0, 1, 0));
	Movement->bUseControllerDesiredRotation = false;
	Movement->bOrientRotationToMovement = false;

	CameraTarget = CreateDefaultSubobject<USceneComponent>(TEXT("CameraTarget"));
	CameraTarget->SetupAttachment(GetRootComponent());
}

void ABotCharacter::BeginPlay()
{
	Super::BeginPlay();
	bIsFacingForward = GetActorRotation().Yaw == 0;
}

void ABotCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	bJumpedThisFrame = false;
}

void ABotCharacter::HorizontalMove(const float& Direction)
{
	const bool MoveForward = Direction > 0;

	if (MoveForward != bIsFacingForward)
		Flip();

	GetCharacterMovement()->MaxWalkSpeed = bRun ? GetRunSpeed() : GetWalkSpeed();
	AddMovementInput(FVector::ForwardVector, Direction, false);
}

void ABotCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	bJumpedThisFrame = true;
}

void ABotCharacter::ThrowObject()
{
	if (!ThrowObjectClass || bIsThrowing || bIsCrouched)
		return;

	UAnimInstance* AnimationInstance = GetMesh()->GetAnimInstance();
	if (!AnimationInstance || !ThrowMontage)
		return;

	// Spawn Object and Attach to the Hand
	ThrowItem = Cast<AThrowableActor>(GetWorld()->SpawnActor(ThrowObjectClass));
	ThrowItem->SetPhysicsEnabled(false);
	ThrowItem->AttachTo(GetMesh(), ThrowSocketName);

	AnimationInstance->Montage_Play(ThrowMontage);
	bIsThrowing = true;
}

void ABotCharacter::ThrowObjectRelease()
{
	ThrowItem->Detach();
	ThrowItem->SetPhysicsEnabled(true);
	const FVector& Forward = IsFlipped() ? FVector::BackwardVector : FVector::ForwardVector;
	FVector Direction = Forward;
	Direction.Normalize();
	const FVector& Impulse = Direction * ThrowForce;
	FVector Velocity = GetMesh()->GetPhysicsLinearVelocity();
	Velocity.Z = Velocity.Y = 0;
	ThrowItem->Throw(Velocity, Impulse);
	bIsThrowing = false;
}

void ABotCharacter::Flip()
{
	if (FlipTween)
		FlipTween->Destroy();

	float StartYaw = 0;
	float TargetYaw = 180;

	if (!bIsFacingForward)
	{
		StartYaw = 180;
		TargetYaw = 0;
	}

	bIsFlipping = true;
	bIsFacingForward = !bIsFacingForward;
	auto Setter = [&](const float& NewYaw) { SetActorRotation(FRotator(0, NewYaw, 0)); };
	FlipTween = FCTween::Play(StartYaw, TargetYaw, Setter, FlipDuration, EFCEase::InOutCubic);
	FlipTween->SetOnComplete([&]() { bIsFlipping = false; });
}
