// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Collectables/CollectableItem.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ACollectableItem::ACollectableItem()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetSimulatePhysics(true);
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollider->SetCollisionObjectType(ECC_WorldDynamic);
	BoxCollider->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	BoxCollider->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	BoxCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	SetRootComponent(BoxCollider);

	SphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereTrigger->SetCollisionObjectType(ECC_WorldDynamic);
	SphereTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereTrigger->SetGenerateOverlapEvents(true);
	SphereTrigger->SetupAttachment(BoxCollider);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BoxCollider);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACollectableItem::BeginPlay()
{
	Super::BeginPlay();
	if (!bUsePhysics)
	{
		BoxCollider->SetSimulatePhysics(false);
		BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ACollectableItem::OnCollected()
{
	if (CollectedSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), CollectedSound, GetActorLocation());

	if (CollectEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollectEffect, GetActorLocation());
	Destroy();
}

void ACollectableItem::OnSpawned()
{
}

void ACollectableItem::SetPhysicsEnabled(bool Enable)
{
	SphereTrigger->SetCollisionEnabled(Enable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);

	if (!bUsePhysics)
		return;

	Internal_SetPhysicsEnabled(Enable);
}

void ACollectableItem::Internal_SetPhysicsEnabled(bool Enable) const
{
	BoxCollider->SetSimulatePhysics(Enable);
	BoxCollider->SetCollisionEnabled(Enable ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
}
