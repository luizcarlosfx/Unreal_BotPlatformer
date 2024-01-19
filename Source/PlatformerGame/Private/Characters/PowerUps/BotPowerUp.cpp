// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PowerUps/BotPowerUp.h"
#include "Characters/BotCharacter.h"
#include "Materials/MaterialInstance.h"

void ABotPowerUp::AttachTo(ABotCharacter* Target)
{
	USkeletalMeshComponent* Mesh = Target->GetMesh();
	const FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, false);

	if (CharacterMaterial)
	{
		PreviousCharacterMaterial = Mesh->GetMaterial(CharacterMaterialIndex);
		Mesh->SetMaterial(CharacterMaterialIndex, CharacterMaterial);
	}

	Character = Target;
	AttachToComponent(Mesh, Rules, CharacterSocketName);
}

void ABotPowerUp::Remove()
{
	if (PreviousCharacterMaterial)
		Character->GetMesh()->SetMaterial(CharacterMaterialIndex, PreviousCharacterMaterial);

	Destroy();
}

void ABotPowerUp::BeginInput()
{
}

void ABotPowerUp::EndInput()
{
}
