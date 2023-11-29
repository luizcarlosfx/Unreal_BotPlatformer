// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BotCharacter.h"
#include "Animation/AnimInstance.h"
#include "BotAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API UBotAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	bool InTheAir;
	UPROPERTY(BlueprintReadOnly)
	bool IsWalking;
	UPROPERTY(BlueprintReadOnly)
	float NormalizedRunSpeed;

	UPROPERTY()
	ABotCharacter* Bot;
	UPROPERTY()
	UCharacterMovementComponent* Movement;
};
