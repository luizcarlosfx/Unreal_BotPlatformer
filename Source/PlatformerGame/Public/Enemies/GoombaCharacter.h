// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyCharacter.h"
#include "Characters/BasePlatformerCharacter.h"
#include "GoombaCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API AGoombaCharacter : public ABaseEnemyCharacter
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	bool bIsDead = false;
};
