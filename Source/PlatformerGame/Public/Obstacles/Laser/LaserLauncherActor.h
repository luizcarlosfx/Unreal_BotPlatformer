// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserLauncherActor.generated.h"

UCLASS()
class PLATFORMERGAME_API ALaserLauncherActor : public AActor
{
	GENERATED_BODY()

public:
	ALaserLauncherActor();
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ALaserActor> LaserClass;
	UPROPERTY(EditAnywhere)
	FName TipSocketName = "TipSocket";

	UPROPERTY()
	ALaserActor* Laser;
};
