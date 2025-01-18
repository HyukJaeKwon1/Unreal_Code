// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingCppGameModeBase.h"
#include "ScoreWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "ShootingSaveGame.h"

void AShootingCppGameModeBase::BeginPlay()
{
	// 태어날 때 ScoreWidget을 생성해서 Viewport에 보이게하고싶다.
	check(scoreUIFactory != nullptr);

	auto ui = CreateWidget(GetWorld(), scoreUIFactory);
	scoreUI = Cast<UScoreWidget>(ui);
	scoreUI->AddToViewport();

	highScore = LoadGame(0);
	scoreUI->HighScore->SetText(FText::AsNumber(highScore));
	// 점수와 최고점수를 관리하고싶다.
	// 태어날때 점수를 0점으로 하고 UI도 갱신하고 싶다.
	score = 0;
	scoreUI->Score->SetText(FText::AsNumber(score));
	// AddScore(-score);
	// FString s = FString::FormatAsNumber(score);


	auto PlayerController = GetWorld()->GetFirstPlayerController();
	// 일시정지 하고싶다.
	PlayerController->SetPause(false);
	// 마우스 커서 안보이게 하고싶다.
	PlayerController->SetShowMouseCursor(false);
	// 입력모드를 게임만 하고싶다.
	PlayerController->SetInputMode(FInputModeGameOnly());
}

// 점수를 증가시키고 UI도 갱신하고 싶다.
void AShootingCppGameModeBase::AddScore(int value)
{
	score += value;
	scoreUI->Score->SetText(FText::AsNumber(score));
	// 점수가 최고점수보다 크다면
	if (score > highScore)
	{
		// 최고점수 = 점수 로 갱신 해주고싶다.
		highScore = score;
		scoreUI->HighScore->SetText(FText::AsNumber(highScore));

		SaveGame();
	}
}

int AShootingCppGameModeBase::LoadGame(int defaultValue = 0)
{
	// 1, 파일이 존재하나 ? (슬롯이름)
	if (UGameplayStatics::DoesSaveGameExist(slotName, slotIndex))
	{
		// 2. SGO = Load Slot(슬롯이름, 인덱스번호)
		auto sgo = UGameplayStatics::LoadGameFromSlot(slotName, slotIndex);
		// 3. return SGO->highScoreSave
		UShootingSaveGame* shootSGO = Cast<UShootingSaveGame>(sgo);
		if (shootSGO)
			return shootSGO->highScoreSave;
	}
	return defaultValue;
}

void AShootingCppGameModeBase::SaveGame()
{
	// 1. 저장소는 슬롯이름(HighScore)과 인덱스번호(0)
	// 2. SaveGameObject(SGO)를 생성한다.
	USaveGame* sgo = UGameplayStatics::CreateSaveGameObject(UShootingSaveGame::StaticClass());

	UShootingSaveGame* shootSGO = Cast<UShootingSaveGame>(sgo);

	// 3. SGO->highScoreSave = highScore;
	shootSGO->highScoreSave = highScore;
	// 4. Save Slot(SGO, 슬롯이름, 인덱스번호)
	UGameplayStatics::SaveGameToSlot(shootSGO, slotName, slotIndex);
}
