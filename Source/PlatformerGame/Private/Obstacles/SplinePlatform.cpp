// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/SplinePlatform.h"

#include "Components/InterpToMovementComponent.h"
#include "Components/SplineComponent.h"

// Sets default values
ASplinePlatform::ASplinePlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	Movement = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("Movement"));
	Movement->BehaviourType = EInterpToBehaviourType::PingPong;

	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	Platform->SetupAttachment(RootComponent);

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASplinePlatform::BeginPlay()
{
	Super::BeginPlay();
	const int32 SplinePoints = Spline->GetNumberOfSplinePoints();
	const float SplineLength = Spline->GetSplineLength();
	for (int i = 0; i < SplinePoints; i++)
	{
		Movement->AddControlPointPosition(Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local));
	}
	Movement->Duration = SplineLength / Speed;
	Movement->FinaliseControlPoints();
}

// Called every frame
void ASplinePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
