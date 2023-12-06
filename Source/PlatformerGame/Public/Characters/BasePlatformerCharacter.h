// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasePlatformerCharacter.generated.h"

UCLASS()
class PLATFORMERGAME_API ABasePlatformerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePlatformerCharacter();
	ABasePlatformerCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void HorizontalMove(const float& Direction);
	FORCEINLINE bool IsFlipping() const { return bIsFlipping; }
	FORCEINLINE bool IsFlipped() const { return !bIsFacingForward; }
	FORCEINLINE float GetWalkSpeed() const { return WalkSpeed; }
	FORCEINLINE float GetRunSpeed() const { return RunSpeed; }
	FORCEINLINE void SetRunEnabled(bool bRunEnabled) { bRun = bRunEnabled; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Flip();
	
private:
	UPROPERTY(EditAnywhere)
	float WalkSpeed = 225;
	UPROPERTY(EditAnywhere)
	float RunSpeed = 450;
	UPROPERTY(EditAnywhere)
	float FlipDuration = 0.25f;
	
	bool bIsFacingForward;
	bool bIsFlipping;
	bool bRun = false;
	class FCTweenInstanceFloat* FlipTween;
};
