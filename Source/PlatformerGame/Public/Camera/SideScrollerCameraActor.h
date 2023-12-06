// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SideScrollerCameraActor.generated.h"

UCLASS()
class PLATFORMERGAME_API ASideScrollerCameraActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASideScrollerCameraActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Setup(APlayerController* PlayerController, class ABotCharacter* Character);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Target;

private:
	void CalculateGoalLocation();
	void UpdateCameraLocation(const float& DeltaTime);

private:
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category="Movement")
	FVector2D DesiredScreenPosition = FVector2D(0.35f, 0.35f);
	UPROPERTY(EditAnywhere, Category="Movement")
	FVector2D DeadZone = FVector2D(0.25, 0.25f);
	UPROPERTY(EditAnywhere, Category="Movement")
	FVector2D SoftZone = FVector2D(0.85, 0.85f);
	UPROPERTY(EditAnywhere, Category="Movement")
	FVector2D InterpolationSpeed = FVector2D(2, 4);

	UPROPERTY()
	class ABotCharacter* Character;

	UPROPERTY()
	class APlayerController* Controller;

	float GoalX;
	float GoalZ;
	bool bIsOutsideSoftZoneX;
	bool bIsOutsideSoftZoneY;
	bool bIsFirstFrame;
};
