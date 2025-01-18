// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHPWidget.h"
#include "Components/ProgressBar.h"

void UPlayerHPWidget::SetPercent(int hp, int maxHP)
{
	HPBar->SetPercent((float)hp / maxHP);
}
