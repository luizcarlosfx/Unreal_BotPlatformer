// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Block/BounceBlock.h"

#include "FCTween.h"
#include "Components/BoxComponent.h"

ABounceBlock::ABounceBlock()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABounceBlock::BeginPlay()
{
	Super::BeginPlay();
	DefaultMaterial = Mesh->GetMaterial(0);
}

void ABounceBlock::SetInteractionEnabled(bool Enable)
{
	bInteractionEnabled = Enable;
	Mesh->SetMaterial(0, bInteractionEnabled ? DefaultMaterial : NoInteractionMaterial);
}

void ABounceBlock::Bounce(const FVector& Direction)
{
	const float BounceLength = GetBoxCollision()->GetScaledBoxExtent().Z;
	const FVector& BouncePosition = Direction * BounceLength;

	const float Time = BounceTime / 2;
	Tween(BouncePosition, Time, [&] { BounceComplete(); });
}

void ABounceBlock::BounceComplete()
{
}

void ABounceBlock::OnPlayerHit()
{
	Super::OnPlayerHit();
	if (bInteractionEnabled)
		Bounce(FVector::UpVector);
}

void ABounceBlock::Tween(const FVector& TargetLocation, const float Time, TFunction<void()> OnComplete)
{
	const FVector& StartLocation = Mesh->GetRelativeLocation();
	FCTween::Play(StartLocation, TargetLocation, [&](const FVector& Location) { Mesh->SetRelativeLocation(Location); }, Time)
		->SetYoyo(true)
		->SetOnComplete(OnComplete);
}
