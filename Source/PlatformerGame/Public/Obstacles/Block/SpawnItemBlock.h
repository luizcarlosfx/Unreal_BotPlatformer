// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacles/Block/InteractionBlock.h"
#include "SpawnItemBlock.generated.h"

class ACollectableItem;
/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API ASpawnItemBlock : public AInteractionBlock
{
	GENERATED_BODY()

public:
	ASpawnItemBlock();
	virtual void BeginPlay() override;

protected:
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }
	virtual void Bounce(const FVector& Direction);
	virtual void SpawnItem(const float& Timer);
	virtual void OnPlayerHit() override;

private:
	virtual void TweenMesh(const FVector& TargetLocation, float Time, TFunction<void()> OnComplete = nullptr);
	virtual void TweenItemLocation(const FVector& TargetLocation, float Time, TFunction<void()> OnComplete = nullptr);

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	float BounceTime = 0.15f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACollectableItem> ItemClass;

	UPROPERTY(EditAnywhere)
	int SpawnItemCount = 1;

	UPROPERTY()
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* NoInteractionMaterial;

	int SpawnedCount = 0;

	UPROPERTY()
	ACollectableItem* SpawnedItem;
};
