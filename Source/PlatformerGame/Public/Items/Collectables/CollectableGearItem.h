// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Collectables/CollectableItem.h"
#include "CollectableGearItem.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API ACollectableGearItem : public ACollectableItem
{
	GENERATED_BODY()

public:
	FORCEINLINE uint32 GetAmount() const { return Amount; }
	virtual ECollectableType GetType() override;
private:
	UPROPERTY(EditAnywhere)
	uint32 Amount = 1;
};
