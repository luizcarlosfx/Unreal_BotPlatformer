// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/BaseBotComponent.h"
#include "BotPowerUpManager.generated.h"

class ABotPowerUp;
/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API UBotPowerUpManager : public UBaseBotComponent
{
	GENERATED_BODY()

public:
	bool CollectPowerUp(TSubclassOf<ABotPowerUp> PowerUpClass);
	bool RemovePowerUp();
	ABotPowerUp* GetCurrentPowerUp() const;
	void BeginInput() const;
	void EndInput() const;

private:
	UPROPERTY(VisibleAnywhere)
	ABotPowerUp* CurrentPowerUp;
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<ABotPowerUp> CurrentClass;

	UPROPERTY(EditAnywhere)
	USoundBase* LosePowerUpSound;
};
