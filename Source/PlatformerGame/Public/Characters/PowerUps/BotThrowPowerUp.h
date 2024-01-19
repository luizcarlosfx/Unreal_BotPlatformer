// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PowerUps/BotPowerUp.h"
#include "BotThrowPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API ABotThrowPowerUp : public ABotPowerUp
{
	GENERATED_BODY()

public:
	virtual void AttachTo(ABotCharacter* Target) override;
	virtual void Remove() override;
	virtual void BeginInput() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AThrowableActor> ThrowableClass;
	UPROPERTY()
	class UBotThrowComponent* ThrowComponent;
};
