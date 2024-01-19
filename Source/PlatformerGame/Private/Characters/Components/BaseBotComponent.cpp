// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/BaseBotComponent.h"

void UBaseBotComponent::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ABotCharacter>(GetOwner());
}

bool UBaseBotComponent::PlayMontage(UAnimMontage* Montage) const
{
	return Character->PlayMontage(Montage);
}
