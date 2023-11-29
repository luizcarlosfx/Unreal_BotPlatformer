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
	virtual void BeginPlay() override;
	void Move(const float& Direction, const bool& bShouldRun);

	FORCEINLINE float GetWalkSpeed() const { return WalkSpeed; }
	FORCEINLINE float GetRunSpeed() const { return RunSpeed; }
	FORCEINLINE bool IsFlipping() const { return bIsFlipping; }

private:
	UPROPERTY(EditAnywhere)
	float WalkSpeed = 80;

	UPROPERTY(EditAnywhere)
	float RunSpeed = 160;

	UPROPERTY(EditAnywhere)
	float FlipDuration = 0.25f;
	
	bool IsFacingForward;

	void Flip();
	bool bIsFlipping;

	class FCTweenInstanceFloat* FlipTween;
};
