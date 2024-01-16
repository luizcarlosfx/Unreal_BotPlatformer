// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Abilities/BotThrowItemAbility.h"

#include "Items/ThrowableActor.h"

void UBotThrowItemAbility::ThrowObject()
{
	if (!ThrowObjectClass || bIsThrowing || IsCrouched())
		return;

	if (!PlayMontage(ThrowMontage))
		return;

	// Spawn Object and Attach to the Hand
	ThrowItem = Cast<AThrowableActor>(GetWorld()->SpawnActor(ThrowObjectClass));
	ThrowItem->SetPhysicsEnabled(false);
	ThrowItem->AttachTo(GetMesh(), ThrowSocketName);

	bIsThrowing = true;
}


void UBotThrowItemAbility::ThrowObjectRelease()
{
	ThrowItem->Detach();
	ThrowItem->SetPhysicsEnabled(true);
	const FVector Forward = IsFlipped() ? FVector::BackwardVector : FVector::ForwardVector;
	FVector Direction = Forward;
	Direction.Normalize();
	const FVector& Impulse = Direction * ThrowForce;
	FVector Velocity = GetMesh()->GetPhysicsLinearVelocity();
	Velocity.Z = Velocity.Y = 0;
	ThrowItem->Throw(GetCharacter(), Velocity, Impulse);
	bIsThrowing = false;
}
