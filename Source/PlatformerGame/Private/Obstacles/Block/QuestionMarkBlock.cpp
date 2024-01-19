// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Block/QuestionMarkBlock.h"

void AQuestionMarkBlock::BounceComplete()
{
	Super::BounceComplete();
	SetInteractionEnabled(false);
}
