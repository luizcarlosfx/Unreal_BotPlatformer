// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BasePlatformerCharacter.h"
#include "GoombaCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API AGoombaCharacter : public ABasePlatformerCharacter
{
	GENERATED_BODY()

public:
	AGoombaCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void MoveBlockedBy(const FHitResult& Impact) override;
};
