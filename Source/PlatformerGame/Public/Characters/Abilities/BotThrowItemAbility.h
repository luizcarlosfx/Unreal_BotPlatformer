// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Abilities/BaseBotAbility.h"
#include "BotThrowItemAbility.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API UBotThrowItemAbility : public UBaseBotAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ThrowObject();

	UFUNCTION(BlueprintCallable)
	void ThrowObjectRelease();

private:
	UPROPERTY(EditAnywhere, Category=Throwing)
	UAnimMontage* ThrowMontage;
	UPROPERTY(EditAnywhere, Category=Throwing)
	FName ThrowSocketName = "RightHandSocket";
	UPROPERTY(EditAnywhere, Category=Throwing)
	float ThrowForce = 700;
	UPROPERTY(EditAnywhere, Category=Throwing)
	TSubclassOf<class AThrowableActor> ThrowObjectClass;

	bool bIsThrowing;
	UPROPERTY()
	AThrowableActor* ThrowItem;
};
