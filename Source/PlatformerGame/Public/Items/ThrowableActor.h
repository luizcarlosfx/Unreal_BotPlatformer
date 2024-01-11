// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BotCharacter.h"
#include "GameFramework/Actor.h"
#include "ThrowableActor.generated.h"

UCLASS()
class PLATFORMERGAME_API AThrowableActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AThrowableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	virtual void Throw(APawn* OwnerPawn, const FVector& InheritedVelocity, const FVector& Impulse);
	virtual void SetPhysicsEnabled(const bool& bEnablePhysics);
	void AttachTo(USceneComponent* AttachTo, const FName& SocketName);
	void Detach();

private:
	void Explode();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void Bounce(const FVector& Normal) const;
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	float GravityScale = 2;
	UPROPERTY(EditAnywhere)
	float BounceMultiplier = 1.25f;
	UPROPERTY(EditAnywhere)
	float BounceNormalBoost = 0.35f;
	
	UPROPERTY(EditAnywhere)
	int MaxBounces = 5;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ExplodeEffect;

	FVector LastVelocity;
	bool bIsAttached = false;

	float BounceImpulse;
	int BounceCount = 0;
};
