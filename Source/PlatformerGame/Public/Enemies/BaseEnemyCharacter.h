// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BasePlatformerCharacter.h"
#include "BaseEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API ABaseEnemyCharacter : public ABasePlatformerCharacter
{
	GENERATED_BODY()

public:
	ABaseEnemyCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;
	virtual void MoveBlockedBy(const FHitResult& Impact) override;
	FORCEINLINE bool CanWalkOffLedge() const { return bCanWalkOffLedge; }

protected:
	UFUNCTION()
	void OnNearLedge();

private:
	UPROPERTY(EditAnywhere)
	bool bCanWalkOffLedge = false;
};
