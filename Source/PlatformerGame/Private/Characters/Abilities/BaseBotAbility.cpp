// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Abilities/BaseBotAbility.h"

void UBaseBotAbility::BeginPlay()
{
	Super::BeginPlay();
}

bool UBaseBotAbility::PlayMontage(UAnimMontage* Montage) const
{
	return Character->PlayMontage(Montage);
}
