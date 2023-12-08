// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserActor.generated.h"

class UNiagaraComponent;

UCLASS()
class PLATFORMERGAME_API ALaserActor : public AActor
{
	GENERATED_BODY()

public:
	ALaserActor();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* BeamFX;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* SparkFX;

private:
	UPROPERTY(EditAnywhere)
	FName BeamEndParam = "BeamEnd";
	UPROPERTY(EditAnywhere)
	float MaxLength = 1500;
	UPROPERTY(EditAnywhere)
	float ImpactOffset = 5;
};
