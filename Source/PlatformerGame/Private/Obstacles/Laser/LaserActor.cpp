// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Laser/LaserActor.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

ALaserActor::ALaserActor()
{
	PrimaryActorTick.bCanEverTick = true;
	BeamFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Beam"));
	SetRootComponent(BeamFX);
	SparkFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Sparks"));
	SparkFX->SetupAttachment(BeamFX);
}

void ALaserActor::BeginPlay()
{
	Super::BeginPlay();
}

void ALaserActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector& Start = GetActorLocation();
	const FVector& Forward = GetActorForwardVector();
	const FVector& End = Start + Forward * MaxLength;
	FHitResult Hit;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility))
	{
		const FVector& SparkLocation = Hit.ImpactPoint - Forward * ImpactOffset;
		SparkFX->SetWorldLocation(SparkLocation);
		BeamFX->SetVectorParameter(BeamEndParam, Hit.ImpactPoint);
		AActor* Actor = Hit.GetActor();
		if (Actor && Actor->CanBeDamaged())
			UGameplayStatics::ApplyDamage(Actor, 100, nullptr, this, UDamageType::StaticClass());
	}
}
