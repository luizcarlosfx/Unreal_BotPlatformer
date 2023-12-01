// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BotCharacter.generated.h"

class ASideScrollerCameraActor;

UCLASS()
class PLATFORMERGAME_API ABotCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABotCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void HorizontalMove(const float& Direction);

	FORCEINLINE float GetWalkSpeed() const { return WalkSpeed; }
	FORCEINLINE float GetRunSpeed() const { return RunSpeed; }
	FORCEINLINE bool IsFlipping() const { return bIsFlipping; }
	FORCEINLINE void SetRunEnabled(bool bRunEnabled) { bRun = bRunEnabled; }
	FORCEINLINE bool DidJumpThisFrame() const { return bJumpedThisFrame; }
	FORCEINLINE bool IsFlipped() const { return !bIsFacingForward; }
	FORCEINLINE USceneComponent* GetCameraTarget() const { return CameraTarget; }
	virtual void OnJumped_Implementation() override;

private:
	UPROPERTY(EditAnywhere)
	float WalkSpeed = 80;
	UPROPERTY(EditAnywhere)
	float RunSpeed = 160;
	UPROPERTY(EditAnywhere)
	float FlipDuration = 0.25f;
	UPROPERTY(EditAnywhere)
	float JumpMinHoldTime = 0.1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASideScrollerCameraActor> CameraClass;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* CameraTarget;

	UPROPERTY()
	ASideScrollerCameraActor* Camera;

	bool bIsFacingForward;

	void Flip();
	bool bIsFlipping;
	bool bRun;
	bool bJumpedThisFrame;

	class FCTweenInstanceFloat* FlipTween;
};
