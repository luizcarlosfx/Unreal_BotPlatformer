// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Game/PlatformerPlayerState.h"
#include "BotCollectablesManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMERGAME_API UBotCollectablesManager : public UActorComponent
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class ABotCharacter* Character;
	UPROPERTY()
	class APlayerController* PlayerController;
	UPROPERTY()
	APlatformerPlayerState* PlayerState;
};
