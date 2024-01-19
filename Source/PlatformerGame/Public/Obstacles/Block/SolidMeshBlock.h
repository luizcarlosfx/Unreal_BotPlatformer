// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacles/Block/InteractionBlock.h"
#include "SolidMeshBlock.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API ASolidMeshBlock : public AInteractionBlock
{
	GENERATED_BODY()

public:
	ASolidMeshBlock();
	virtual void BeginPlay() override;

protected:
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }
	void SetInteractionEnabled(bool Enable);

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY()
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* NoInteractionMaterial;

	bool InteractionEnabled = true;
};
