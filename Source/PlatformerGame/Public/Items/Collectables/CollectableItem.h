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

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereCollision;

	virtual void OnCollected();
};
