// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SideScrollerCameraActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CameraConfigTrigger.generated.h"

UCLASS()
class PLATFORMERGAME_API ACameraConfigTrigger : public AActor
{
	GENERATED_BODY()

public:
	ACameraConfigTrigger();
	inline static const FName Tag = "CameraConfigTrigger";
	FORCEINLINE const FCameraBounds& GetCameraBounds() const { return CameraBounds; }

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	FCameraBounds CameraBounds;
};
