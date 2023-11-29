// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BotCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABotCharacter::ABotCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABotCharacter::Move(const float& Direction, const bool& bShouldRun)
{
	const float Speed = bShouldRun ? RunSpeed : WalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	AddMovementInput(GetActorForwardVector(), Direction * Speed, false);
}
