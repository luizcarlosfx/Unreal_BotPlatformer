// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlatformerCharacter.h"
#include "BotCharacter.generated.h"

class ASideScrollerCameraActor;
class AThrowableActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);

UCLASS()
class PLATFORMERGAME_API ABotCharacter : public ABasePlatformerCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnDie OnDie;
	// Sets default values for this character's properties
	ABotCharacter();
	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE bool DidJumpThisFrame() const { return bJumpedThisFrame; }
	FORCEINLINE USceneComponent* GetCameraTarget() const { return CameraTarget; }
	virtual void OnJumped_Implementation() override;
	virtual void Landed(const FHitResult& Hit) override;

	void ThrowObject();

	UFUNCTION(BlueprintCallable)
	void ThrowObjectRelease();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	FORCEINLINE bool IsDead() const { return bIsDead; }

	bool PlayMontage(UAnimMontage* Montage) const;

private:
	UPROPERTY(EditAnywhere)
	float JumpMinHoldTime = 0.1;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* CameraTarget;

	UPROPERTY(EditAnywhere, Category=Throwing)
	UAnimMontage* ThrowMontage;
	UPROPERTY(EditAnywhere, Category=Throwing)
	FName ThrowSocketName = "RightHandSocket";
	UPROPERTY(EditAnywhere, Category=Throwing)
	float ThrowForce = 1000;
	UPROPERTY(EditAnywhere, Category=Throwing)
	TSubclassOf<class AThrowableActor> ThrowObjectClass;

	bool bJumpedThisFrame;
	bool bIsThrowing;

	UPROPERTY()
	AThrowableActor* ThrowItem;

	bool bIsDead = false;
};
