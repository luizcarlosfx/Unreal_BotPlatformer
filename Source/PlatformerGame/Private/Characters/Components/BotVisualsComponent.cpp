// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/BotVisualsComponent.h"

void UBotVisualsComponent::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInterface* MaterialInterface = GetMesh()->GetMaterial(0);
	DefaultMaterial = UMaterialInstanceDynamic::Create(MaterialInterface, nullptr);
	InternalSetMaterial(DefaultMaterial);
}

void UBotVisualsComponent::ApplyMaterial(UMaterialInterface* Material)
{
	if (!Material)
		return;

	UMaterialInstanceDynamic* Instance = UMaterialInstanceDynamic::Create(Material, nullptr);
	InternalSetMaterial(Instance);
	bCustomMaterialApplied = true;
}

void UBotVisualsComponent::InternalSetMaterial(UMaterialInstanceDynamic* Material)
{
	CurrentMaterial = Material;
	GetMesh()->SetMaterial(0, CurrentMaterial);
	UpdateBlink();
}

void UBotVisualsComponent::UpdateBlink() const
{
	CurrentMaterial->SetScalarParameterValue(BlinkProperty, bBlinkEnabled ? BlinkSpeed : 0);
}

void UBotVisualsComponent::ResetMaterial()
{
	if (!bCustomMaterialApplied)
		return;

	InternalSetMaterial(DefaultMaterial);
}

void UBotVisualsComponent::SetBlinkEnabled(bool bEnable)
{
	bBlinkEnabled = bEnable;
	UpdateBlink();
}
