// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Block/SolidMeshBlock.h"

ASolidMeshBlock::ASolidMeshBlock()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASolidMeshBlock::BeginPlay()
{
	Super::BeginPlay();
	DefaultMaterial = Mesh->GetMaterial(0);
}

void ASolidMeshBlock::SetInteractionEnabled(bool Enable)
{
	InteractionEnabled = Enable;
	Mesh->SetMaterial(0, InteractionEnabled ? DefaultMaterial : NoInteractionMaterial);
}
