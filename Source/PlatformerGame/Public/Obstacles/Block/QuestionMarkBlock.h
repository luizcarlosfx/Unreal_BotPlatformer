// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BounceBlock.h"
#include "QuestionMarkBlock.generated.h"

class ACollectableItem;
/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API AQuestionMarkBlock : public ABounceBlock
{
	GENERATED_BODY()

protected:
	virtual void BounceComplete() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACollectableItem> CollectableClass;
};
