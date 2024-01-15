// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BotCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/ThrowableActor.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABotCharacter::ABotCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

void ABotCharacter::ThrowObject()
{
	if (!ThrowObjectClass || bIsThrowing || bIsCrouched)
		return;

	if (!PlayMontage(ThrowMontage))
		return;

	// Spawn Object and Attach to the Hand
	ThrowItem = Cast<AThrowableActor>(GetWorld()->SpawnActor(ThrowObjectClass));
	ThrowItem->SetPhysicsEnabled(false);
	ThrowItem->AttachTo(GetMesh(), ThrowSocketName);

	bIsThrowing = true;
}

void ABotCharacter::ThrowObjectRelease()
{
	ThrowItem->Detach();
	ThrowItem->SetPhysicsEnabled(true);
	const FVector Forward = IsFlipped() ? FVector::BackwardVector : FVector::ForwardVector;
	FVector Direction = Forward;
	Direction.Normalize();
	const FVector& Impulse = Direction * ThrowForce;
	FVector Velocity = GetMesh()->GetPhysicsLinearVelocity();
	Velocity.Z = Velocity.Y = 0;
	ThrowItem->Throw(this, Velocity, Impulse);
	bIsThrowing = false;
}

float ABotCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsDead)
		return 0;

	bIsDead = true;
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
		PlayerController->DisableInput(PlayerController);
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
