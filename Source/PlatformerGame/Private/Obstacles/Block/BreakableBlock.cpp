// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Block/BreakableBlock.h"

#include "Components/BoxComponent.h"
#include "Field/FieldSystemComponent.h"
#include "Field/FieldSystemTypes.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Kismet/GameplayStatics.h"

ABreakableBlock::ABreakableBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	Geometry = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("Geometry"));
	Geometry->SetEnableGravity(true);
	Geometry->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Geometry->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	Geometry->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	Geometry->SetCollisionObjectType(ECC_WorldStatic);
	Geometry->SetSimulatePhysics(false);
	Geometry->SetupAttachment(RootComponent);

	FieldSystem = CreateDefaultSubobject<UFieldSystemComponent>(TEXT("FieldSystem"));
	FieldSystem->SetupAttachment(Geometry);

	RadialFalloff = CreateDefaultSubobject<URadialFalloff>("RadialFalloff");
	RadialFalloff->SetRadialFalloff(100, 0, 1, 0, 100, FVector::Zero(), Field_FallOff_None);

	RadialVector = CreateDefaultSubobject<URadialVector>("RadialVector");
	RadialVector->SetRadialVector(400, FVector::Zero());

	UniformVector = CreateDefaultSubobject<UUniformVector>("UniformVector");
	UniformVector->SetUniformVector(300, FVector::UpVector);
}

void ABreakableBlock::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!bIsBroken)
		return;

	UniformVector->SetUniformVector(ExtraGravity, FVector::DownVector);
	// add upwards velocity
	FieldSystem->ApplyPhysicsField(true, EFieldPhysicsType::Field_LinearForce, nullptr, UniformVector);
}

void ABreakableBlock::OnPlayerHit()
{
	Super::OnPlayerHit();
	if (!bIsBroken)
		Break();
}

void ABreakableBlock::Break()
{
	UBoxComponent* Box = GetBoxCollision();
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Geometry->SetSimulatePhysics(true);

	// center of the box
	FVector BoxLocation = Box->GetComponentLocation();
	RadialFalloff->Position = BoxLocation;

	// Move to the bottom center of the box
	BoxLocation.Z -= Box->GetScaledBoxExtent().Z;

	RadialVector->Position = BoxLocation;

	// break
	FieldSystem->ApplyPhysicsField(true, EFieldPhysicsType::Field_InternalClusterStrain, nullptr, RadialFalloff);

	// add upwards velocity
	FieldSystem->ApplyPhysicsField(true, EFieldPhysicsType::Field_LinearVelocity, nullptr, UniformVector);

	// adds radial force
	FieldSystem->ApplyPhysicsField(true, EFieldPhysicsType::Field_LinearVelocity, nullptr, RadialVector);

	UGameplayStatics::PlaySoundAtLocation(this, BreakSound, Box->GetComponentLocation());
	bIsBroken = true;
	SetLifeSpan(BreakLifespan);
}
