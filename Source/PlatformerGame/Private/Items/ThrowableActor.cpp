// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ThrowableActor.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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
void AThrowableActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	LastVelocity = Mesh->GetPhysicsLinearVelocity();
	if (bIsAttached)
		return;

	//apply gravity manually
	const float Force = GetWorld()->GetGravityZ() * Mesh->GetMass() * GravityScale;
	Mesh->AddForce(FVector::UpVector * Force);
}

void AThrowableActor::Throw(APawn* OwnerPawn, const FVector& InheritedVelocity, const FVector& Impulse)
{
	BounceImpulse = Impulse.Length() * BounceMultiplier;
	SetOwner(OwnerPawn);
	SetInstigator(OwnerPawn);
	Mesh->SetPhysicsLinearVelocity(InheritedVelocity);
	Mesh->AddImpulse(Impulse, NAME_None, true);
}

void AThrowableActor::SetPhysicsEnabled(const bool& bEnablePhysics)
{
	Mesh->SetCollisionEnabled(bEnablePhysics ? ECollisionEnabled::PhysicsOnly : ECollisionEnabled::NoCollision);
	Mesh->SetSimulatePhysics(bEnablePhysics);
}

void AThrowableActor::AttachTo(USceneComponent* AttachTo, const FName& SocketName)
{
	const FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, false);
	Mesh->AttachToComponent(AttachTo, Rules, SocketName);
	bIsAttached = true;
}

void AThrowableActor::Detach()
{
	const FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld, false);
	Mesh->DetachFromComponent(Rules);
	bIsAttached = false;
}

void AThrowableActor::Explode()
{
	if (ExplodeEffect)
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplodeEffect, GetActorLocation());

	Destroy();
}

void AThrowableActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor)
		return;

	if (OtherActor->CanBeDamaged())
	{
		UGameplayStatics::ApplyDamage(OtherActor, 100, GetInstigator()->GetController(), this, UDamageType::StaticClass());
		Explode();
		return;
	}

	const FVector& Normal = Hit.ImpactNormal;

	const double Dot = FVector::DotProduct(FVector::UpVector, Normal);
	const double AngleRadians = FMath::Acos(Dot);
	const double AngleDegrees = FMath::RadiansToDegrees(AngleRadians);

	if (BounceCount >= MaxBounces || AngleDegrees > 80)
	{
		Explode();
	}
	else
	{
		BounceCount++;
		Bounce(Normal);
	}
}

void AThrowableActor::Bounce(const FVector& Normal) const
{
	const float VelocityXSign = FMath::Sign(LastVelocity.X);
	FVector Direction = FVector(VelocityXSign, 0, FMath::Sign(LastVelocity.Z));
	Direction.Normalize();
	Direction = FMath::GetReflectionVector(Direction, FVector::UpVector);

	// the idea behind all this math is to keep the jump height visually the same no matter where it's boucing
	// adds normal X to the velocity Z
	float NormalBoost = FMath::Abs(Normal.X) * BounceNormalBoost;

	// if the normal is pointing to the same direction as the velocity then I want a smaller "jump"
	if (VelocityXSign == FMath::Sign(Normal.X))
		NormalBoost *= -1;

	Direction.Z += NormalBoost;

	const FVector& Velocity = Direction * BounceImpulse;
	Mesh->SetPhysicsLinearVelocity(Velocity);
}
