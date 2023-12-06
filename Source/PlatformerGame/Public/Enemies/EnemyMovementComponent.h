// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API UEnemyMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNearToLedgeSignature);

public:
	UPROPERTY(BlueprintAssignable, Category="Movement")
	FNearToLedgeSignature OnNearLedge;

	virtual bool CheckFall(const FFindFloorResult& OldFloor, const FHitResult& Hit, const FVector& Delta, const FVector& OldLocation, float remainingTime, float timeTick,
	                       int32 Iterations, bool bMustJump) override;
};
