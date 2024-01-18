// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectableItem.generated.h"

UCLASS()
class PLATFORMERGAME_API ACollectableItem : public AActor
{
	GENERATED_BODY()

public:
	ACollectableItem();
	virtual void OnCollected();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere)
	class USoundBase* CollectedSound;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* CollectEffect;
};
