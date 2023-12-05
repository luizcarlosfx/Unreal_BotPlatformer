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
	virtual void Tick(float DeltaTime) override;
	virtual void Throw(const FVector& InheritedVelocity, const FVector& Impulse);
	virtual void SetPhysicsEnabled(const bool& bEnablePhysics);
	void AttachTo(USceneComponent* AttachTo, const FName& SocketName) const;
	void Detach() const;

private:
	void Explode();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ExplodeEffect;

	FVector LastVelocity;
};
