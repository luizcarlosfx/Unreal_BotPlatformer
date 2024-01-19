// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/BotThrowComponent.h"

#include "Items/ThrowableActor.h"

void UBotThrowComponent::ThrowObject()
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


void UBotThrowComponent::ThrowObjectRelease()
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

void UBotThrowComponent::SetThrowableClass(TSubclassOf<AThrowableActor> ThrowableClass)
{
	ThrowObjectClass = ThrowableClass;
}
