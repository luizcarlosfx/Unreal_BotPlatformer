// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/BaseBotComponent.h"
#include "BotVisualsComponent.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API UBotVisualsComponent : public UBaseBotComponent
{
	GENERATED_BODY()

public:
	void ApplyMaterial(UMaterialInterface* Material);
	void ResetMaterial();
	void SetBlinkEnabled(bool bEnable);

protected:
	virtual void BeginPlay() override;

private:
	void InternalSetMaterial(UMaterialInstanceDynamic* Material);
	void UpdateBlink() const;
private:
	UPROPERTY(EditAnywhere)
	float BlinkSpeed = 2;

	UPROPERTY(EditAnywhere)
	FName BlinkProperty = "BlinkSpeed";
	
	UPROPERTY()
	UMaterialInstanceDynamic* DefaultMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* CurrentMaterial;
	bool bCustomMaterialApplied;
	bool bBlinkEnabled;
};
