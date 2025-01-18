// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingCppGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAMECPP_API AShootingCppGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// 태어날 때 ScoreWidget을 생성해서 Viewport에 보이게하고싶다.
	// 점수와 최고점수를 관리하고싶다.
	// 태어날때 점수를 0점으로 하고 UI도 갱신하고 싶다.
	// 총알이 적을 파괴하면 점수를 1점 증가시키고 싶다. + UI도 갱신하고 싶다.
public:

	int score;
	int highScore;

	void AddScore(int value);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UScoreWidget> scoreUIFactory;

	UPROPERTY()
	class UScoreWidget* scoreUI;
private:

	FString slotName = TEXT("HighScore");
	int slotIndex = 0;

	int LoadGame(int defaultValue);
	void SaveGame();
};
