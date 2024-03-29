// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BotPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/SideScrollerCameraActor.h"
#include "Characters/BotCharacter.h"
#include "Characters/Components/BotPowerUpManager.h"

void ABotPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputContext, 0);
	}

	if (!CameraClass)
		return;

	Bot = Cast<ABotCharacter>(GetCharacter());
	SideScrollerCamera = GetWorld()->SpawnActor<ASideScrollerCameraActor>(CameraClass.Get());
	SideScrollerCamera->Setup(this, Bot);
}

void ABotPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Bot = Cast<ABotCharacter>(InPawn);
	if (SideScrollerCamera)
		SideScrollerCamera->Setup(this, Bot);
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

	// second jump will always be small
	if (Bot->JumpCurrentCountPreJump >= 1)
	{
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(
			UnusedHandle, this, &ABotPlayerController::StopJumping, Bot->JumpMaxHoldTime * 0.5f, false);
	}
}

void ABotPlayerController::JumpReleased(const FInputActionValue& ActionValue)
{
	StopJumping();
}

void ABotPlayerController::RunPressed(const FInputActionValue& ActionValue)
{
	Bot->SetRunEnabled(true);
	Bot->GetPowerUpManager()->BeginInput();
}

void ABotPlayerController::RunReleased(const FInputActionValue& ActionValue)
{
	Bot->SetRunEnabled(false);
	Bot->GetPowerUpManager()->EndInput();
}

void ABotPlayerController::StopJumping()
{
	Bot->StopJumping();
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
	Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &ABotPlayerController::JumpReleased);
	Input->BindAction(RunAction, ETriggerEvent::Started, this, &ABotPlayerController::RunPressed);
	Input->BindAction(RunAction, ETriggerEvent::Completed, this, &ABotPlayerController::RunReleased);
}
