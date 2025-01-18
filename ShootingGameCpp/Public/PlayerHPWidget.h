// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAMECPP_API UPlayerHPWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* HPBar;
	void SetPercent(int hp, int maxHP);
};
