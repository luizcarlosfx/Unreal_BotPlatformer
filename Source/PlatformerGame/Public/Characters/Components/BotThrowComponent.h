// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/BaseBotComponent.h"
#include "BotThrowComponent.generated.h"

class AThrowableActor;
/**
 * 
 */
UCLASS(Blueprintable)
class PLATFORMERGAME_API UBotThrowComponent : public UBaseBotComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ThrowObject();

	UFUNCTION(BlueprintCallable)
	void ThrowObjectRelease();

	void SetThrowableClass(TSubclassOf<AThrowableActor> ThrowableClass);
private:
	UPROPERTY(EditAnywhere, Category=Throwing)
	UAnimMontage* ThrowMontage;
	UPROPERTY(EditAnywhere, Category=Throwing)
	FName ThrowSocketName = "RightHandSocket";
	UPROPERTY(EditAnywhere, Category=Throwing)
	float ThrowForce = 700;
	UPROPERTY(EditAnywhere, Category=Throwing)
	TSubclassOf<AThrowableActor> ThrowObjectClass;

	bool bIsThrowing;
	UPROPERTY()
	AThrowableActor* ThrowItem;
};
