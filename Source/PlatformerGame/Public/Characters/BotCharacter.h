// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BotCharacter.generated.h"

UCLASS()
class PLATFORMERGAME_API ABotCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABotCharacter();
	void Move(const float& Direction, const bool& bShouldRun);

private:
	UPROPERTY(EditAnywhere)
	float WalkSpeed = 80;

	UPROPERTY(EditAnywhere)
	float RunSpeed = 160;
};
