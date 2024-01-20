// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PlatformerGameMode.h"

#include "Characters/BotCharacter.h"
#include "Game/PlatformerPlayerState.h"
#include "Kismet/GameplayStatics.h"

void APlatformerGameMode::BeginPlay()
{
	Super::BeginPlay();
	Player = UGameplayStatics::GetPlayerController(this, 0);
	PlayerState = Player->GetPlayerState<APlatformerPlayerState>();
	AssignOnPlayerDieEvent();
}

void APlatformerGameMode::FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation)
{
	Super::FinishRestartPlayer(NewPlayer, StartRotation);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, NewPlayer->GetPawn()->GetActorLabel());
}

void APlatformerGameMode::AssignOnPlayerDieEvent()
{
	ACharacter* Character = Player->GetCharacter();
	Bot = Cast<ABotCharacter>(Character);
	Bot->OnDie.AddDynamic(this, &APlatformerGameMode::OnPlayerDie);
}

void APlatformerGameMode::OnPlayerDie()
{
	PlayerState->Died();
	Player->DisableInput(Player);
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, [&] { Respawn(); }, RespawnTime, false);
}

void APlatformerGameMode::Respawn()
{
	Bot->Destroy();
	RestartPlayer(Player);
	Player->EnableInput(Player);
}
