// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraConfigTrigger.h"

#include "Components/BoxComponent.h"

ACameraConfigTrigger::ACameraConfigTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->SetGenerateOverlapEvents(true);
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box->SetCollisionResponseToAllChannels(ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);
	Tags.Add(Tag);
}
