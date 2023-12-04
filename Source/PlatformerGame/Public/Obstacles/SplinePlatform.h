// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplinePlatform.generated.h"

UCLASS()
class PLATFORMERGAME_API ASplinePlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASplinePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	class USplineComponent* Spline;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Platform;

	UPROPERTY(VisibleAnywhere)
	class UInterpToMovementComponent* Movement;

	UPROPERTY(EditAnywhere)
	float Speed = 100;
};
