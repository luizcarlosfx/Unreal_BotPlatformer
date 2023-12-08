// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Laser/LaserLauncherActor.h"
#include "Obstacles/Laser/LaserActor.h"

ALaserLauncherActor::ALaserLauncherActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void ALaserLauncherActor::BeginPlay()
{
	Super::BeginPlay();
	Laser = Cast<ALaserActor>(GetWorld()->SpawnActor(LaserClass));
	// const FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, false);
	const FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	Laser->AttachToComponent(Mesh, Rules, TipSocketName);
}
