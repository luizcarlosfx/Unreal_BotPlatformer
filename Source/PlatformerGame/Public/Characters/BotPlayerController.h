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
	UInputAction* MovementInput;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* ActionInput;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* JumpInput;
	
	bool IsActionButtonPressed() const;
	
	void AxisChanged(const FInputActionValue& ActionValue);
	void JumpPressed(const FInputActionValue& ActionValue);
	void ActionPressed(const FInputActionValue& ActionValue);

	UPROPERTY()
	class ABotCharacter* Bot;

	struct FEnhancedInputActionValueBinding* ActionMappingValue;
};
