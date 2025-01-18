// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ShootingSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAMECPP_API UShootingSaveGame : public USaveGame
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 highScoreSave;

};
