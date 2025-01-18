// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerActor.h"
#include "Components/ArrowComponent.h"
#include "EnemyActor.h"

// Sets default values
AEnemyManagerActor::AEnemyManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));

	SetRootComponent(root);

	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("arrow"));

	arrow->SetupAttachment(root);
	// arrow를 회전하고싶다.
	// Pitch=-90.0000, Yaw=0.000000, Roll=180.000000)
	arrow->SetWorldRotation(FRotator(-90, 0, 180));
}

// Called when the game starts or when spawned
void AEnemyManagerActor::BeginPlay()
{
	Super::BeginPlay();
	// makeTime을 정하고싶다.
	// 1. 태어날 때
	makeTime = FMath::RandRange(minTime, maxTime);
}

// Called every frame
void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 시간이 흐르다가
	currentTime += DeltaTime;
	// 만약 현재시간이 생성시간을 초과했다면
	if (currentTime > makeTime)
	{
		// 현재시간을 0으로 초기화 하고싶다.
		currentTime = 0;
		// 적 공장에서 적을 만들어서 Arrow위치에 배치하고 싶다.
		GetWorld()->SpawnActor<AEnemyActor>(enemyFactory, arrow->GetComponentTransform());

		// makeTime을 정하고싶다.
		// 2. Enemy를 Spawn하고 나서
		makeTime = FMath::RandRange(minTime, maxTime);
	}
}

