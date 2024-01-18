// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Collectables/CollectableItem.h"
#include "CollectablePowerUpItem.generated.h"

class UBaseBotAbility;
/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API ACollectablePowerUpItem : public ACollectableItem
{
	GENERATED_BODY()

public:
	virtual ECollectableType GetType() override;
	FORCEINLINE TSubclassOf<UBaseBotAbility> GetBotAbilityClass() const { return BotAbilityClass; }

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UBaseBotAbility> BotAbilityClass;
};
