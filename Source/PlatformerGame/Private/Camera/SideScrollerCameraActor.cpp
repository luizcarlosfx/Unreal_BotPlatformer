// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/SideScrollerCameraActor.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASideScrollerCameraActor::ASideScrollerCameraActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ASideScrollerCameraActor::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTarget(this);
}

// Called every frame
void ASideScrollerCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASideScrollerCameraActor::SetTarget(USceneComponent* NewTarget)
{
	Target = NewTarget;
}
