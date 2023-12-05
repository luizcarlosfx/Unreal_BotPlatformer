// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BasePlatformerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FCTween.h"

// Sets default values
ABasePlatformerCharacter::ABasePlatformerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bConstrainToPlane = true;
	Movement->SetPlaneConstraintNormal(FVector(0, 1, 0));
	Movement->bUseControllerDesiredRotation = false;
	Movement->bOrientRotationToMovement = false;
}

void ABasePlatformerCharacter::BeginPlay()
{
	Super::BeginPlay();
	bIsFacingForward = GetActorRotation().Yaw == 0;
}

void ABasePlatformerCharacter::HorizontalMove(const float& Direction)
{
	const bool MoveForward = Direction > 0;

	if (MoveForward != bIsFacingForward)
		Flip();

	GetCharacterMovement()->MaxWalkSpeed = bRun ? GetRunSpeed() : GetWalkSpeed();
	AddMovementInput(FVector::ForwardVector, Direction, false);
}

void ABasePlatformerCharacter::Flip()
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
