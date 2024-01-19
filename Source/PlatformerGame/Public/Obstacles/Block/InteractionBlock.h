// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionBlock.generated.h"

class UBoxComponent;

UCLASS()
class PLATFORMERGAME_API AInteractionBlock : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractionBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void OnPlayerHit();

	FORCEINLINE UBoxComponent* GetBoxCollision() const { return BoxCollision; }

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;
};
