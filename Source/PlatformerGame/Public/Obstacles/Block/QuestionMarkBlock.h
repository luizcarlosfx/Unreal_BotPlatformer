// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SolidMeshBlock.h"
#include "QuestionMarkBlock.generated.h"

class ACollectableItem;
/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API AQuestionMarkBlock : public ASolidMeshBlock
{
	GENERATED_BODY()

protected:
	virtual void OnPlayerHit() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACollectableItem> CollectableClass;
};
