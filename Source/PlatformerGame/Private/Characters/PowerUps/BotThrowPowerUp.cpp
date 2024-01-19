// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PowerUps/BotThrowPowerUp.h"

#include "Characters/BotCharacter.h"
#include "Characters/Components/BotThrowComponent.h"

void ABotThrowPowerUp::AttachTo(ABotCharacter* Target)
{
	Super::AttachTo(Target);
	ThrowComponent = Target->GetThrowBehaviour();
	ThrowComponent->SetThrowableClass(ThrowableClass);
}

void ABotThrowPowerUp::Remove()
{
	ThrowComponent->SetThrowableClass(nullptr);
	Super::Remove();
}

void ABotThrowPowerUp::BeginInput()
{
	Super::BeginInput();
	ThrowComponent->ThrowObject();
}
