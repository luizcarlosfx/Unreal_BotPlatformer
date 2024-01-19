// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectableItem.generated.h"

UENUM()
enum ECollectableType
{
	ECT_None,
	ECT_Coin,
	ECT_PowerUp
};

UCLASS(Abstract)
class PLATFORMERGAME_API ACollectableItem : public AActor
{
	GENERATED_BODY()

public:
	ACollectableItem();
	virtual void SetPhysicsEnabled(bool Enable);
	virtual void BeginPlay() override;
	virtual void OnCollected();
	virtual void OnSpawned();

	FORCEINLINE bool GetAutoCollectOnSpawn() const { return bAutoCollectOnSpawn; }

	virtual ECollectableType GetType()
	{
		return ECT_None;
	}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereTrigger;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollider;

private:
	UPROPERTY(EditAnywhere)
	class USoundBase* CollectedSound;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* CollectEffect;

	UPROPERTY(EditAnywhere)
	bool bUsePhysics = true;

	UPROPERTY(EditAnywhere)
	bool bAutoCollectOnSpawn = false;

	UPROPERTY(EditAnywhere)
	class USoundBase* SpawnSound;

private:
	void Internal_SetPhysicsEnabled(bool Enable) const;
};
