// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PowerUps/BotPowerUp.h"
#include "Characters/BotCharacter.h"
#include "Characters/Components/BotVisualsComponent.h"
#include "Materials/MaterialInstance.h"

void ABotPowerUp::AttachTo(ABotCharacter* Target)
{
	USkeletalMeshComponent* Mesh = Target->GetMesh();
	const FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, false);

	if (CharacterMaterial)
		Target->GetVisuals()->ApplyMaterial(CharacterMaterial);

	Character = Target;
	AttachToComponent(Mesh, Rules, CharacterSocketName);
}

void ABotPowerUp::Remove()
{
	if (CharacterMaterial)
		Character->GetVisuals()->ResetMaterial();

	Destroy();
}

void ABotPowerUp::BeginInput()
{
}

void ABotPowerUp::EndInput()
{
}
