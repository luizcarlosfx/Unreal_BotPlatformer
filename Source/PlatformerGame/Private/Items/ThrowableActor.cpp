// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ThrowableActor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AThrowableActor::AThrowableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
}

// Called when the game starts or when spawned
void AThrowableActor::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddDynamic(this, &AThrowableActor::OnHit);
}

// Called every frame
void AThrowableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LastVelocity = Mesh->GetPhysicsLinearVelocity();
	// Mesh->SetPhysicsLinearVelocity(MoveDirection * Speed);
}

void AThrowableActor::Throw(const FVector& InheritedVelocity, const FVector& Impulse)
{
	Mesh->SetPhysicsLinearVelocity(InheritedVelocity);
	Mesh->AddImpulse(Impulse, NAME_None, true);
}

void AThrowableActor::SetPhysicsEnabled(const bool& bEnablePhysics)
{
	Mesh->SetCollisionEnabled(bEnablePhysics ? ECollisionEnabled::PhysicsOnly : ECollisionEnabled::NoCollision);
	Mesh->SetSimulatePhysics(bEnablePhysics);
}

void AThrowableActor::AttachTo(USceneComponent* AttachTo, const FName& SocketName) const
{
	const FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, false);
	Mesh->AttachToComponent(AttachTo, Rules, SocketName);
}

void AThrowableActor::Detach() const
{
	const FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld, false);
	Mesh->DetachFromComponent(Rules);
}

void AThrowableActor::Explode()
{
	if (ExplodeEffect)
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplodeEffect, GetActorLocation());

	Destroy();
}

void AThrowableActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	const FVector& Normal = Hit.ImpactNormal;
	if (FMath::Abs(Normal.X) > FMath::Abs(Normal.Z))
	{
		Explode();
	}
	FVector Velocity = LastVelocity;
	Velocity = FMath::GetReflectionVector(Velocity, Normal);
	Mesh->SetPhysicsLinearVelocity(Velocity);
}
