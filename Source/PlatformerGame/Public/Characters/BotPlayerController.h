// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "BotPlayerController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;
class ASideScrollerCameraActor;

UCLASS()
class PLATFORMERGAME_API ABotPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* InputContext;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* RunAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASideScrollerCameraActor> CameraClass;

	void AxisReleased(const FInputActionValue& ActionValue);
	void AxisChanged(const FInputActionValue& ActionValue);
	void JumpPressed(const FInputActionValue& ActionValue);
	void JumpReleased(const FInputActionValue& ActionValue);
	void RunPressed(const FInputActionValue& ActionValue);
	void RunReleased(const FInputActionValue& ActionValue);
	void StopJumping();

	UPROPERTY()
	class ABotCharacter* Bot;

	UPROPERTY()
	ASideScrollerCameraActor* SideScrollerCamera;
};
