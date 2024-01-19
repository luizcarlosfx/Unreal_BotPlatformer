// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/BotPowerUpManager.h"

#include "Characters/PowerUps/BotPowerUp.h"
#include "Kismet/GameplayStatics.h"

bool UBotPowerUpManager::CollectPowerUp(TSubclassOf<ABotPowerUp> PowerUpClass)
{
	if (!PowerUpClass)
		return false;

	if (CurrentPowerUp)
	{
		if (PowerUpClass == CurrentClass)
			return false;

		ABotPowerUp* Current = GetCurrentPowerUp();
		Current->Remove();
	}

	ABotPowerUp* PowerUp = Cast<ABotPowerUp>(GetWorld()->SpawnActor(PowerUpClass));
	CurrentClass = PowerUpClass;
	CurrentPowerUp = PowerUp;
	PowerUp->AttachTo(GetCharacter());
	return true;
}

bool UBotPowerUpManager::RemovePowerUp()
{
	if (!CurrentPowerUp)
		return false;

	if (LosePowerUpSound)
		UGameplayStatics::PlaySound2D(this, LosePowerUpSound);

	CurrentPowerUp->Remove();
	CurrentPowerUp = nullptr;
	CurrentClass = nullptr;
	return true;
}

ABotPowerUp* UBotPowerUpManager::GetCurrentPowerUp() const
{
	return CurrentPowerUp;
}

void UBotPowerUpManager::BeginInput() const
{
	if (CurrentPowerUp)
		CurrentPowerUp->BeginInput();
}

void UBotPowerUpManager::EndInput() const
{
	if (CurrentPowerUp)
		CurrentPowerUp->EndInput();
}
