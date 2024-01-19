// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBotComponent.h"
#include "Components/ActorComponent.h"
#include "Game/PlatformerPlayerState.h"
#include "BotCollectablesManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLATFORMERGAME_API UBotCollectablesManager : public UBaseBotComponent
{
	GENERATED_BODY()

public:
	void Collect(class ACollectableItem* Collectable) const;

protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class APlayerController* PlayerController;
	UPROPERTY()
	APlatformerPlayerState* PlayerState;
};
