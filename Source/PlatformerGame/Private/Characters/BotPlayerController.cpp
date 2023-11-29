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

bool ABotPlayerController::IsActionButtonPressed() const
{
	return ActionMappingValue->GetValue().Get<bool>();
}

void ABotPlayerController::AxisChanged(const FInputActionValue& ActionValue)
{
	const FVector2D& Axis = ActionValue.Get<FVector2D>();
	const double MoveDirection = Axis.X;

	if (FMath::Abs(MoveDirection) > 0)
		Bot->Move(MoveDirection, IsActionButtonPressed());
}

void ABotPlayerController::JumpPressed(const FInputActionValue& ActionValue)
{
	Bot->Jump();
}

void ABotPlayerController::ActionPressed(const FInputActionValue& ActionValue)
{
}

void ABotPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);

	if (!Input)
		return;

	Input->BindAction(MovementInput, ETriggerEvent::Triggered, this, &ABotPlayerController::AxisChanged);
	Input->BindAction(JumpInput, ETriggerEvent::Started, this, &ABotPlayerController::JumpPressed);
	Input->BindAction(ActionInput, ETriggerEvent::Started, this, &ABotPlayerController::ActionPressed);

	ActionMappingValue = &Input->BindActionValue(ActionInput);
}
