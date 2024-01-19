// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Block/QuestionMarkBlock.h"

void AQuestionMarkBlock::OnPlayerHit()
{
	Super::OnPlayerHit();
	SetInteractionEnabled(false);
}
