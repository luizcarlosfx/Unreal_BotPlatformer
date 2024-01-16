// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/PlatformerPlayerState.h"

void APlatformerPlayerState::CollectGears(uint32 amount)
{
	Gears += amount;
	if (Gears > 100)
		Gears -= 100;

	OnCollectGear.Broadcast(Gears);
	AdjustLife(1);
}

void APlatformerPlayerState::AdjustLife(int amount)
{
	Lives = FMath::Clamp(Lives + amount, 0, 99);
	OnGainLife.Broadcast(Lives);
}
