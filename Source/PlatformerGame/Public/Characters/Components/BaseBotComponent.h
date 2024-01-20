// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BotCharacter.h"
#include "Components/ActorComponent.h"
#include "BaseBotComponent.generated.h"


class ABotCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLATFORMERGAME_API UBaseBotComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ABotCharacter* GetCharacter() const { return Character; }

	FORCEINLINE bool IsFlipped() const { return Character->IsFlipped(); }
	FORCEINLINE bool IsFlipping() const { return Character->IsFlipped(); }
	FORCEINLINE bool IsCrouched() const { return Character->bIsCrouched; }
	FORCEINLINE USkinnedMeshComponent* GetMesh() const { return Character->GetMesh(); }
	FORCEINLINE UCharacterMovementComponent* GetCharacterMovement() const { return Character->GetCharacterMovement(); }

	bool PlayMontage(UAnimMontage* Montage) const;

private:
	UPROPERTY()
	ABotCharacter* Character;
};