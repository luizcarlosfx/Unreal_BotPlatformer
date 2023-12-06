// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/GoombaCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


AGoombaCharacter::AGoombaCharacter()
{
}

void AGoombaCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->PerchRadiusThreshold = GetCapsuleComponent()->GetScaledCapsuleRadius();
}

void AGoombaCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const UCharacterMovementComponent* Movement = GetCharacterMovement();
	const bool bCanWalk = Movement->CheckLedgeDirection(GetActorLocation(), GetVelocity() * 0.5f,
	                                                    FVector::DownVector);
	if (!bCanWalk && !IsFlipping())
		Flip();

	const int Direction = IsFlipped() ? -1 : 1;
	HorizontalMove(Direction);
}

void AGoombaCharacter::MoveBlockedBy(const FHitResult& Impact)
{
	Super::MoveBlockedBy(Impact);

	const FVector& Forward = GetActorForwardVector();
	const FVector& Normal = Impact.ImpactNormal;

	if (FVector::DotProduct(Forward, Normal) < 0)
		Flip();
}
