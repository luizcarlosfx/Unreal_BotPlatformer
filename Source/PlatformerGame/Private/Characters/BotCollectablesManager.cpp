// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BotCollectablesManager.h"

#include "Characters/BotCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Items/Collectables/CollectableItem.h"

void UBotCollectablesManager::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ABotCharacter>(GetOwner());
	Character->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &UBotCollectablesManager::OnBeginOverlap);
}

void UBotCollectablesManager::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                             bool bFromSweep, const FHitResult& SweepResult)
{
	ACollectableItem* Collectable = Cast<ACollectableItem>(OtherActor);
	Collectable->OnCollected();
}
