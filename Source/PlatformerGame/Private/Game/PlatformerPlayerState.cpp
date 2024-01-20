// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/PlatformerPlayerState.h"

void APlatformerPlayerState::CollectGears(uint32 amount)
{
	Gears += amount;
	if (Gears >= 100)
	{
		Gears -= 100;
		AdjustLife(1);
	}

	OnCollectGear.Broadcast(Gears);
}

void APlatformerPlayerState::AdjustLife(int amount)
{
	if (amount > 0)
		OnGainLife.Broadcast(Lives);

	Lives = FMath::Clamp(Lives + amount, 0, 99);
}

void APlatformerPlayerState::Died()
{
	AdjustLife(-1);
	OnDie.Broadcast();
}
