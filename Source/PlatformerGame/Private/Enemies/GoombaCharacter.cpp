// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/GoombaCharacter.h"
#include "FCTween.h"

void AGoombaCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const int Direction = IsFlipped() ? -1 : 1;
	HorizontalMove(Direction);
}

float AGoombaCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsDead)
		return 0;

	bIsDead = true;
	FCTween::Play(GetActorScale(), FVector::ZeroVector, [&](const FVector& Scale) { SetActorRelativeScale3D(Scale); }, 0.15f)
		->SetOnComplete([&]() { Destroy(); });
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
