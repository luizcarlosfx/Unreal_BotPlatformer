// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/BotCollectablesManager.h"

#include "Characters/BotCharacter.h"
#include "Characters/Components/BaseBotComponent.h"
#include "Characters/Components/BotPowerUpManager.h"
#include "Characters/PowerUps/BotPowerUp.h"
#include "Components/CapsuleComponent.h"
#include "Game/PlatformerPlayerState.h"
#include "Items/Collectables/CollectableGearItem.h"
#include "Items/Collectables/CollectableItem.h"
#include "Items/Collectables/CollectablePowerUpItem.h"
#include "Kismet/GameplayStatics.h"

void UBotCollectablesManager::BeginPlay()
{
	Super::BeginPlay();
	GetCharacter()->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &UBotCollectablesManager::OnBeginOverlap);
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerState = PlayerController->GetPlayerState<APlatformerPlayerState>();
}

void UBotCollectablesManager::Collect(ACollectableItem* Collectable) const
{
	if (!Collectable)
		return;

	Collectable->OnCollected();

	if (Collectable->GetType() == ECT_Coin && PlayerState)
	{
		const ACollectableGearItem* Gear = Cast<ACollectableGearItem>(Collectable);
		PlayerState->CollectGears(Gear->GetAmount());
	}
	else if (Collectable->GetType() == ECT_PowerUp)
	{
		const ACollectablePowerUpItem* PowerUp = Cast<ACollectablePowerUpItem>(Collectable);

		if (PowerUp && PowerUp->GetPowerUpClass())
		{
			GetCharacter()->GetPowerUpManager()->CollectPowerUp(PowerUp->GetPowerUpClass());
		}
	}
}

void UBotCollectablesManager::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                             bool bFromSweep, const FHitResult& SweepResult)
{
	ACollectableItem* Collectable = Cast<ACollectableItem>(OtherActor);
	Collect(Collectable);
}
