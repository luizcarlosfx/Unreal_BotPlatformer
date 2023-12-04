// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/DestructibleBrick.h"

#include "Components/BoxComponent.h"
#include "Field/FieldSystemComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Kismet/GameplayStatics.h"

ADestructibleBrick::ADestructibleBrick()
{
	PrimaryActorTick.bCanEverTick = true;

	Geometry = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("Geometry"));
	Geometry->SetEnableGravity(true);
	Geometry->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Geometry->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	Geometry->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	Geometry->SetCollisionObjectType(ECC_WorldStatic);
	Geometry->SetSimulatePhysics(false);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetCollisionObjectType(ECC_WorldStatic);
	BoxCollision->SetupAttachment(Geometry);
	BoxCollision->SetSimulatePhysics(false);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	FieldSystem = CreateDefaultSubobject<UFieldSystemComponent>(TEXT("FieldSystem"));
	FieldSystem->SetupAttachment(Geometry);

	RadialFalloff = CreateDefaultSubobject<URadialFalloff>("RadialFalloff");
	RadialFalloff->SetRadialFalloff(100, 0, 1, 0, 100, FVector::Zero(), Field_FallOff_None);

	RadialVector = CreateDefaultSubobject<URadialVector>("RadialVector");
	RadialVector->SetRadialVector(400, FVector::Zero());

	UniformVector = CreateDefaultSubobject<UUniformVector>("UniformVector");
	UniformVector->SetUniformVector(300, FVector::UpVector);

	SetRootComponent(Geometry);
}

void ADestructibleBrick::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentHit.AddDynamic(this, &ADestructibleBrick::OnHit);
}

void ADestructibleBrick::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!bIsDestroyed)
		return;

	UniformVector->SetUniformVector(ExtraGravity, FVector::DownVector);
	// add upwards velocity
	FieldSystem->ApplyPhysicsField(true, EFieldPhysicsType::Field_LinearForce, nullptr, UniformVector);
}


void ADestructibleBrick::Break()
{
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Geometry->SetSimulatePhysics(true);

	// center of the box
	FVector BoxLocation = BoxCollision->GetComponentLocation();
	RadialFalloff->Position = BoxLocation;

	// Move to the bottom center of the box
	BoxLocation.Z -= BoxCollision->GetScaledBoxExtent().Z;

	RadialVector->Position = BoxLocation;

	// break
	FieldSystem->ApplyPhysicsField(true, EFieldPhysicsType::Field_InternalClusterStrain, nullptr, RadialFalloff);

	// add upwards velocity
	FieldSystem->ApplyPhysicsField(true, EFieldPhysicsType::Field_LinearVelocity, nullptr, UniformVector);

	// adds radial force
	FieldSystem->ApplyPhysicsField(true, EFieldPhysicsType::Field_LinearVelocity, nullptr, RadialVector);

	UGameplayStatics::PlaySoundAtLocation(this, BreakSound, BoxCollision->GetComponentLocation());
	bIsDestroyed = true;
	SetLifeSpan(BreakLifespan);
}

void ADestructibleBrick::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->ActorHasTag("Player"))
		return;

	const double Dot = FVector::DotProduct(Hit.ImpactNormal, FVector::UpVector);

	if (FMath::Abs(Dot - 1) < 0.001)
		Break();
}
