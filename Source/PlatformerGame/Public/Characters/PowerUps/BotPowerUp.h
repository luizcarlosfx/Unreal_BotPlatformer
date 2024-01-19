// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BotPowerUp.generated.h"

class ABotCharacter;
class UMaterialInstance;

UCLASS()
class PLATFORMERGAME_API ABotPowerUp : public AActor
{
	GENERATED_BODY()

public:
	virtual void AttachTo(ABotCharacter* Target);
	virtual void Remove();
	virtual void BeginInput();
	virtual void EndInput();

private:
	UPROPERTY(EditAnywhere)
	UMaterialInterface* CharacterMaterial;
	UPROPERTY(EditAnywhere)
	int CharacterMaterialIndex = 0;

	UPROPERTY(EditAnywhere)
	FName CharacterSocketName = NAME_None;

	UPROPERTY()
	ABotCharacter* Character;

	UPROPERTY()
	UMaterialInterface* PreviousCharacterMaterial;
};
