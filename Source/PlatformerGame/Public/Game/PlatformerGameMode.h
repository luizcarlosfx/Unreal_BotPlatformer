// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlatformerPlayerState.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformerGameMode.generated.h"



/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API APlatformerGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation) override;

private:
	void AssignOnPlayerDieEvent();
	UFUNCTION()
	void OnPlayerDie();
	UFUNCTION()
	void Respawn();
private:
	UPROPERTY(EditAnywhere)
	float RespawnTime = 2;
	UPROPERTY()
	APlayerController* Player;
	UPROPERTY()
	class ABotCharacter* Bot;
	UPROPERTY()
	APlatformerPlayerState* PlayerState;
};
