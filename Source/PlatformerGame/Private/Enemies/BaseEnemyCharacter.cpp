// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/BaseEnemyCharacter.h"

#include "Characters/BotCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Enemies/EnemyMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseEnemyCharacter::ABaseEnemyCharacter(const FObjectInitializer& ObjectInitializer) : Super(
	ObjectInitializer.SetDefaultSubobjectClass(CharacterMovementComponentName, UEnemyMovementComponent::StaticClass()))
{
}

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	UEnemyMovementComponent* Movement = Cast<UEnemyMovementComponent>(GetCharacterMovement());
	Movement->PerchRadiusThreshold = GetCapsuleComponent()->GetScaledCapsuleRadius();
	Movement->bCanWalkOffLedges = bCanWalkOffLedge;
	Movement->OnNearLedge.AddDynamic(this, &ABaseEnemyCharacter::OnNearLedge);
}

void ABaseEnemyCharacter::MoveBlockedBy(const FHitResult& Impact)
{
	Super::MoveBlockedBy(Impact);
	if (IsFlipping())
		return;

	const FVector& Forward = GetActorForwardVector();
	const FVector& Normal = Impact.ImpactNormal;

	if (FVector::DotProduct(Forward, Normal) < 0)
	{
		AActor* Actor = Impact.GetActor();
		if (ABotCharacter* Bot = Cast<ABotCharacter>(Actor))
			UGameplayStatics::ApplyDamage(Bot, 1, GetController(), this, UDamageType::StaticClass());
		else
			Flip();
	}
}

void ABaseEnemyCharacter::OnNearLedge()
{
	if (!IsFlipping())
		Flip();
}
