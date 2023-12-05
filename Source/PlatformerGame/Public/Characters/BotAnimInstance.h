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

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void Notify_ReleaseObject() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool InTheAir;
	UPROPERTY(BlueprintReadOnly)
	bool IsWalking;
	UPROPERTY(BlueprintReadOnly)
	float NormalizedRunSpeed;

	UPROPERTY(BlueprintReadOnly)
	bool IsCrouched;

	UPROPERTY(BlueprintReadOnly)
	bool JumpedThisFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABotCharacter* Bot;
	UPROPERTY()
	UCharacterMovementComponent* Movement;
};
