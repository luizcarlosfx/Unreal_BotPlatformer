// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Block/SpawnItemBlock.h"
#include "Items/Collectables/CollectableItem.h"

#include "FCTween.h"
#include "Characters/BotCharacter.h"
#include "Characters/Components/BotCollectablesManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ASpawnItemBlock::ASpawnItemBlock()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASpawnItemBlock::BeginPlay()
{
	Super::BeginPlay();
	DefaultMaterial = Mesh->GetMaterial(0);
}

void ASpawnItemBlock::Bounce(const FVector& Direction)
{
	const float BounceLength = GetBoxCollision()->GetScaledBoxExtent().Z;
	const FVector& BouncePosition = Direction * BounceLength;

	const float Time = BounceTime / 2;
	TweenMesh(BouncePosition, Time, [&]
	{
		SpawnedCount++;
		if (SpawnedCount >= SpawnItemCount)
		{
			Mesh->SetMaterial(0, NoInteractionMaterial);
		}
	});
	SpawnItem(BounceTime);
}

void ASpawnItemBlock::SpawnItem(const float& Timer)
{
	if (!ItemClass)
		return;

	const FVector& ActorLocation = GetActorLocation();
	SpawnedItem = Cast<ACollectableItem>(GetWorld()->SpawnActor(ItemClass, &ActorLocation));

	SpawnedItem->OnSpawned();
	SpawnedItem->SetPhysicsEnabled(false);

	const float& BounceMultiplier = SpawnedItem->GetAutoCollectOnSpawn() ? 4 : 2;
	const float& BounceAmount = GetBoxCollision()->GetScaledBoxExtent().Z * BounceMultiplier;
	const FVector& TargetLocation = SpawnedItem->GetActorLocation() + SpawnedItem->GetActorUpVector() * BounceAmount;

	TweenItemLocation(TargetLocation, Timer, [&]
	{
		if (SpawnedItem->GetAutoCollectOnSpawn())
		{
			ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			if (const ABotCharacter* Bot = Cast<ABotCharacter>(Character))
				Bot->GetCollectablesManager()->Collect(SpawnedItem);
		}
		else
		{
			SpawnedItem->SetPhysicsEnabled(true);
		}
	});
}

void ASpawnItemBlock::OnPlayerHit()
{
	Super::OnPlayerHit();
	if (SpawnedCount < SpawnItemCount)
		Bounce(FVector::UpVector);
}

void ASpawnItemBlock::TweenMesh(const FVector& TargetLocation, const float Time, TFunction<void()> OnComplete)
{
	const FVector& StartLocation = Mesh->GetRelativeLocation();
	FCTween::Play(StartLocation, TargetLocation, [&](const FVector& Location) { Mesh->SetRelativeLocation(Location); }, Time)
		->SetYoyo(true)
		->SetOnComplete(OnComplete);
}

void ASpawnItemBlock::TweenItemLocation(const FVector& TargetLocation, float Time, TFunction<void()> OnComplete)
{
	const FVector& StartLocation = SpawnedItem->GetActorLocation();
	FCTween::Play(StartLocation, TargetLocation, [&](const FVector& Location) { SpawnedItem->SetActorLocation(Location); }, Time)
		->SetOnComplete(OnComplete);
}
