// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManagerActor.generated.h"

UCLASS()
class SHOOTINGGAMECPP_API AEnemyManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 시간이 흐르다가 생성시간이 되면 적 공장에서 적을 만들어서 Arrow위치에 배치하고 싶다.
	// 생성시간을 매번 바꾸고 싶다. 최솟값, 최대값
	// 속성(멤버변수)
	// 현재시간, 생성시간, 적 공장 Arrow
	float currentTime;
	float makeTime = 2;
	// makeTime을 정하고싶다.
	// 1. 태어날 때
	// 2. Enemy를 Spawn하고 나서
	UPROPERTY(EditAnywhere)
	float minTime = 1;

	UPROPERTY(EditAnywhere)
	float maxTime = 3;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyActor> enemyFactory;

	UPROPERTY(EditAnywhere)
	class USceneComponent* root;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* arrow;
};
