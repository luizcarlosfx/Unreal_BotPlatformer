// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlatformerPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCollectGear, int, Gears);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGainLife, int, Lives);

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API APlatformerPlayerState : public APlayerState
{
	GENERATED_BODY()
	

public:
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnCollectGear OnCollectGear;

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnGainLife OnGainLife;

	void CollectGears(uint32 amount);
	void AdjustLife(int amount);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetLives() const { return Lives; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetGears() const { return Gears; }

private:
	int Lives = 5;
	int Gears = 0;
};
