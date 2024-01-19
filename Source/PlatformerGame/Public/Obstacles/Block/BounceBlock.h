// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacles/Block/InteractionBlock.h"
#include "BounceBlock.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API ABounceBlock : public AInteractionBlock
{
	GENERATED_BODY()

public:
	ABounceBlock();
	virtual void BeginPlay() override;

protected:
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }
	void SetInteractionEnabled(bool Enable);
	virtual void Bounce(const FVector& Direction);
	virtual void BounceComplete();
	virtual void OnPlayerHit() override;

private:
	virtual void Tween(const FVector& TargetLocation, float Time, TFunction<void()> OnComplete = nullptr);

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	float BounceTime = 0.15f;

	UPROPERTY()
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* NoInteractionMaterial;

	bool bInteractionEnabled = true;
};
