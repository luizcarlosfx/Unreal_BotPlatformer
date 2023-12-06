// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyMovementComponent.h"

bool UEnemyMovementComponent::CheckFall(const FFindFloorResult& OldFloor, const FHitResult& Hit, const FVector& Delta, const FVector& OldLocation, float remainingTime,
                                        float timeTick, int32 Iterations, bool bMustJump)
{
	if (!CanWalkOffLedges())
	{
		if (OnNearLedge.IsBound())
			OnNearLedge.Broadcast();
	}
	return Super::CheckFall(OldFloor, Hit, Delta, OldLocation, remainingTime, timeTick, Iterations, bMustJump);
}
