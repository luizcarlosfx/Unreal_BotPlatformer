// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BotPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/BotCharacter.h"

void ABotPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputContext, 0);
	}

	Bot = Cast<ABotCharacter>(GetCharacter());
}

void ABotPlayerController::AxisReleased(const FInputActionValue& ActionValue)
{
	if (Bot->bIsCrouched)
		Bot->UnCrouch();
}

void ABotPlayerController::AxisChanged(const FInputActionValue& ActionValue)
{
	const FVector2D& Axis = ActionValue.Get<FVector2D>();
	const double MoveDirection = Axis.X;

	if (FMath::Abs(MoveDirection) > 0)
		Bot->HorizontalMove(MoveDirection);

	const float& VerticalInput = Axis.Y;
	const bool bShouldCrouch = VerticalInput < 0;

	if (bShouldCrouch != Bot->bIsCrouched)
	{
		if (bShouldCrouch)
			Bot->Crouch();
		else
			Bot->UnCrouch();
	}
}

void ABotPlayerController::JumpPressed(const FInputActionValue& ActionValue)
{
	Bot->Jump();
}

void ABotPlayerController::RunPressed(const FInputActionValue& ActionValue)
{
	Bot->SetRunEnabled(true);
}

void ABotPlayerController::RunReleased(const FInputActionValue& ActionValue)
{
	Bot->SetRunEnabled(false);
}

void ABotPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);

	if (!Input)
		return;

	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABotPlayerController::AxisChanged);
	Input->BindAction(MoveAction, ETriggerEvent::Completed, this, &ABotPlayerController::AxisReleased);
	Input->BindAction(JumpAction, ETriggerEvent::Started, this, &ABotPlayerController::JumpPressed);
	Input->BindAction(RunAction, ETriggerEvent::Started, this, &ABotPlayerController::RunPressed);
	Input->BindAction(RunAction, ETriggerEvent::Completed, this, &ABotPlayerController::RunReleased);
}
