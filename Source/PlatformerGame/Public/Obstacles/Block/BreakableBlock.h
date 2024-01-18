// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacles/Block/InteractionBlock.h"
#include "BreakableBlock.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API ABreakableBlock : public AInteractionBlock
{
	GENERATED_BODY()

public:
	ABreakableBlock();
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void OnPlayerHit() override;
	FORCEINLINE UGeometryCollectionComponent* GetGeometry() const { return Geometry; }

private:
	void Break();

private:
	UPROPERTY(VisibleAnywhere)
	class UGeometryCollectionComponent* Geometry;
	UPROPERTY(VisibleAnywhere)
	class UFieldSystemComponent* FieldSystem;
	UPROPERTY(VisibleAnywhere)
	class URadialFalloff* RadialFalloff;
	UPROPERTY(VisibleAnywhere)
	class URadialVector* RadialVector;
	UPROPERTY(VisibleAnywhere)
	class UUniformVector* UniformVector;
	UPROPERTY(EditAnywhere)
	class USoundBase* BreakSound;
	UPROPERTY(EditAnywhere)
	float BreakLifespan = 3;
	UPROPERTY(EditAnywhere)
	float ExtraGravity = 100;

	bool bIsBroken;
};
