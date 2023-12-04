// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleBrick.generated.h"

UCLASS()
class PLATFORMERGAME_API ADestructibleBrick : public AActor
{
	GENERATED_BODY()

public:
	ADestructibleBrick();
	UFUNCTION()
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UGeometryCollectionComponent* Geometry;

private:
	void Break();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;
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
	
	bool bIsDestroyed;
};
