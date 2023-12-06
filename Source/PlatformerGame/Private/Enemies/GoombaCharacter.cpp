// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/GoombaCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void AGoombaCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AGoombaCharacter::OnHit);
}

void AGoombaCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const bool bCanWalk = GetCharacterMovement()->CurrentFloor.IsWalkableFloor();

	int Direction = IsFlipped() ? -1 : 1;

	// flip
	if (!bCanWalk)
		Direction *= -1;

	HorizontalMove(Direction);
}

void AGoombaCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (IsFlipping())
		return;

	const FVector& Forward = GetActorForwardVector();
	const FVector& Normal = Hit.ImpactNormal;

	if (FVector::DotProduct(Forward, Normal) < 0)
		Flip();
}
