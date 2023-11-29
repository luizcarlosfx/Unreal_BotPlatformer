// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BotCharacter.h"

#include "FCTween.h"
#include "GameFramework/CharacterMovementComponent.h"

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
}

void ABotCharacter::BeginPlay()
{
	Super::BeginPlay();
	IsFacingForward = GetActorRotation().Yaw == 0;
}

void ABotCharacter::Move(const float& Direction, const bool& bShouldRun)
{
	const bool MoveForward = Direction > 0;

	if (MoveForward != IsFacingForward)
		Flip();

	const float Speed = bShouldRun ? RunSpeed : WalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	AddMovementInput(FVector::ForwardVector, Direction, false);
}

void ABotCharacter::Flip()
{
	if (FlipTween)
		FlipTween->Destroy();

	float StartYaw = 0;
	float TargetYaw = 180;

	if(!IsFacingForward)
	{
		StartYaw = 180;
		TargetYaw = 0;
	}
	
	bIsFlipping = true;
	IsFacingForward = !IsFacingForward;
	auto Setter = [&](const float& NewYaw) { SetActorRotation(FRotator(0, NewYaw, 0)); };
	FlipTween = FCTween::Play(StartYaw, TargetYaw, Setter, FlipDuration, EFCEase::InOutCubic);
	FlipTween->SetOnComplete([&]() { bIsFlipping = false; });
}
