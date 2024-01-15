// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Block/InteractionBlock.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AInteractionBlock::AInteractionBlock()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetCollisionObjectType(ECC_WorldStatic);
	BoxCollision->SetupAttachment(GetRootComponent());
	BoxCollision->SetSimulatePhysics(false);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
}

// Called when the game starts or when spawned
void AInteractionBlock::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentHit.AddDynamic(this, &AInteractionBlock::OnHit);
}

void AInteractionBlock::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->ActorHasTag("Player"))
		return;

	if (ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor))
	{
		const bool bInTheAir = PlayerCharacter->GetMovementComponent()->IsFalling();

		if (!bInTheAir)
			return;

		const double Dot = FVector::DotProduct(Hit.ImpactNormal, FVector::UpVector);
		const double Angle = FMath::RadiansToDegrees(FMathf::ACos(Dot));

		if (Angle > 1)
			return;

		PlayerCharacter->StopJumping();
		OnPlayerHit();
	}

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, Hit.ImpactNormal.GetSafeNormal().ToString());
}

void AInteractionBlock::OnPlayerHit()
{
}
