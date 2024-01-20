// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BotCharacter.h"

#include "Characters/Components/BotCollectablesManager.h"
#include "Characters/Components/BotPowerUpManager.h"
#include "Characters/Components/BotThrowComponent.h"
#include "Characters/Components/BotVisualsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABotCharacter::ABotCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollectablesManager = CreateDefaultSubobject<UBotCollectablesManager>(TEXT("CollectablesManager"));
	ThrowComponent = CreateDefaultSubobject<UBotThrowComponent>(TEXT("ThrowComponent"));
	PowerUpManager = CreateDefaultSubobject<UBotPowerUpManager>(TEXT("PowerUpManager"));
	Visuals = CreateDefaultSubobject<UBotVisualsComponent>(TEXT("Visuals"));
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bConstrainToPlane = true;
	Movement->SetPlaneConstraintNormal(FVector(0, 1, 0));
	Movement->bUseControllerDesiredRotation = false;
	Movement->bOrientRotationToMovement = false;
	CameraTarget = CreateDefaultSubobject<USceneComponent>(TEXT("CameraTarget"));
	CameraTarget->SetupAttachment(GetRootComponent());
}

void ABotCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	bJumpedThisFrame = false;
}

void ABotCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	bJumpedThisFrame = true;
}

void ABotCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	AActor* Actor = Hit.GetActor();

	if (Actor && Actor->CanBeDamaged())
	{
		UGameplayStatics::ApplyDamage(Actor, 100, GetController(), this, UDamageType::StaticClass());
		GetCharacterMovement()->AddImpulse(FVector::UpVector * 100, true);
	}
}

float ABotCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsDead || !bCanTakeDamage)
		return 0;

	if (PowerUpManager->GetCurrentPowerUp())
	{
		PowerUpManager->RemovePowerUp();

		// can't take damage for a time
		GetVisuals()->SetBlinkEnabled(true);
		bCanTakeDamage = false;
		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, [&]
		                                {
			                                bCanTakeDamage = true;
			                                GetVisuals()->SetBlinkEnabled(false);
		                                },
		                                DamageInterval, false);

		return DamageAmount;
	}

	bIsDead = true;
	OnDie.Broadcast();

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

bool ABotCharacter::PlayMontage(UAnimMontage* Montage) const
{
	UAnimInstance* AnimationInstance = GetMesh()->GetAnimInstance();
	if (!AnimationInstance || !Montage)
		return false;

	AnimationInstance->Montage_Play(Montage);
	return true;
}
