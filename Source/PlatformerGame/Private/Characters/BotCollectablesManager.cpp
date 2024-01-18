// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BotCollectablesManager.h"

#include "Characters/BotCharacter.h"
#include "Characters/Abilities/BaseBotAbility.h"
#include "Components/CapsuleComponent.h"
#include "Game/PlatformerPlayerState.h"
#include "Items/Collectables/CollectableGearItem.h"
#include "Items/Collectables/CollectableItem.h"
#include "Items/Collectables/CollectablePowerUpItem.h"

void UBotCollectablesManager::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ABotCharacter>(GetOwner());
	Character->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &UBotCollectablesManager::OnBeginOverlap);
	PlayerController = Cast<APlayerController>(Character->GetController());
	PlayerState = PlayerController->GetPlayerState<APlatformerPlayerState>();
}

void UBotCollectablesManager::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                             bool bFromSweep, const FHitResult& SweepResult)
{
	ACollectableItem* Collectable = Cast<ACollectableItem>(OtherActor);
	Collectable->OnCollected();

	if (Collectable->GetType() == ECT_Coin && PlayerState)
	{
		const ACollectableGearItem* Gear = Cast<ACollectableGearItem>(OtherActor);
		PlayerState->CollectGears(Gear->GetAmount());
	}
	else if (Collectable->GetType() == ECT_PowerUp)
	{
		const ACollectablePowerUpItem* PowerUp = Cast<ACollectablePowerUpItem>(OtherActor);

		if (PowerUp && PowerUp->GetBotAbilityClass())
		{
			UActorComponent* SpawnedComponent = Character->AddComponentByClass(PowerUp->GetBotAbilityClass(), false, FTransform::Identity, false);
			UBaseBotAbility* SpawnedAbility = Cast<UBaseBotAbility>(SpawnedComponent);

			
		}
	}
}
