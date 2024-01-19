// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BotAnimInstance.h"

#include "Characters/BotCharacter.h"
#include "Characters/Components/BotThrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBotAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (ABotCharacter* Character = Cast<ABotCharacter>(TryGetPawnOwner()))
	{
		Bot = Character;
		Movement = Character->GetCharacterMovement();
	}
}

void UBotAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Movement)
		return;

	const FVector& Velocity = Bot->GetVelocity();
	const float AbsoluteGroundVelocity = FMath::Abs(Velocity.X);
	const float CurrentVelocity = FMath::Max(AbsoluteGroundVelocity, 0);
	NormalizedRunSpeed = CurrentVelocity / Bot->GetRunSpeed();
	InTheAir = Movement->IsFalling();
	IsWalking = (!InTheAir && Bot->IsFlipping()) || AbsoluteGroundVelocity > 0;
	IsCrouched = Bot->bIsCrouched;
	IsAlive = !Bot->IsDead();
	JumpedThisFrame = Bot->DidJumpThisFrame();
}

void UBotAnimInstance::Notify_ReleaseObject() const
{
	Bot->GetThrowBehaviour()->ThrowObjectRelease();
}
