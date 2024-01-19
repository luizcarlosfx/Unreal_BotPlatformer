// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlatformerCharacter.h"
#include "BotCharacter.generated.h"

class ASideScrollerCameraActor;
class UBotThrowComponent;
class UBotPowerUpManager;

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
	FORCEINLINE UBotThrowComponent* GetThrowBehaviour() const { return ThrowComponent; }
	virtual void OnJumped_Implementation() override;
	virtual void Landed(const FHitResult& Hit) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	FORCEINLINE bool IsDead() const { return bIsDead; }

	bool PlayMontage(UAnimMontage* Montage) const;
	FORCEINLINE UBotPowerUpManager* GetPowerUpManager() const { return PowerUpManager; }

private:
	UPROPERTY(VisibleAnywhere)
	class UBotCollectablesManager* CollectablesManager;
	UPROPERTY(VisibleAnywhere)
	UBotPowerUpManager* PowerUpManager;
	UPROPERTY(VisibleAnywhere)
	UBotThrowComponent* ThrowComponent;

	UPROPERTY(EditAnywhere)
	float DamageInterval = 1;

	UPROPERTY(EditAnywhere)
	float JumpMinHoldTime = 0.1;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* CameraTarget;

	bool bJumpedThisFrame;

	bool bIsDead = false;
	double LastDamageTime = 0;
};
