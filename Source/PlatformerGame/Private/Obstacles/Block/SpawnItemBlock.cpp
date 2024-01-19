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
	TweenMesh(BouncePosition, Time, [&] { SpawnItem(); });
}

void ASpawnItemBlock::SpawnItem()
{
	if (!ItemClass)
		return;

	const FVector& ActorLocation = GetActorLocation();
	ACollectableItem* Item = Cast<ACollectableItem>(GetWorld()->SpawnActor(ItemClass, &ActorLocation));
	Item->OnSpawned();
	Item->SetPhysicsEnabled(false);
	SpawnedItem = Item;

	const FVector& TargetLocation = SpawnedItem->GetActorLocation() + SpawnedItem->GetActorUpVector() * GetBoxCollision()->GetScaledBoxExtent().Z * 2;

	TweenItemLocation(TargetLocation, BounceTime, [&]
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

	if (SpawnCount < SpawnItems)
		Mesh->SetMaterial(0, NoInteractionMaterial);
}

void ASpawnItemBlock::OnPlayerHit()
{
	Super::OnPlayerHit();
	if (SpawnCount < SpawnItems)
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
