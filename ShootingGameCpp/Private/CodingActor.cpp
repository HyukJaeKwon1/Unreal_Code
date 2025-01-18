// Fill out your copyright notice in the Description page of Project Settings.


#include "CodingActor.h"
#include "Kismet/GameplayStatics.h"
#include <iostream>

// Sets default values
ACodingActor::ACodingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodingActor::BeginPlay()
{
	Super::BeginPlay();

	// 배열에 10개 항목을 넣는데 1이상 2이하값을 랜덤으로 누적해서 넣기
	//float sum = 0;
	//for (int i = 0; i < 10; i++)
	//{
	//	sum += FMath::RandRange(1.0f, 2.0f);
	//	notes.Add(sum);
	//	// UE_LOG(LogTemp, Warning, TEXT("%.2f"), sum);
	//}

	//int result = Add(10, 20);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), result);







	//array.Add(1);	// 0번
	//array.Add(2);	// 1번
	//array.Add(3);	// 2번

	//array.Remove(1);	//값을 찾아서 지움 -> 0번 삭제
	//array.RemoveAt(1);	// 1번 인덱스 삭제 -> 2 삭제

	//array.Insert(10, 2);	// 2번 인덱스에 10 삽입

	//int32 temp = array[0];
	//if (!array.Contains<int32>(2)) //2 포함되어있지않으면
	//{
	//	array.Add(2);
	//}

	//TMap<FString, int32> map;
	//// AGE라는 키가 없으면 추가해서 넣고
	//// 있으면 20을 그 곳에 넣고싶다.
	//if (false == map.Contains(TEXT("AGE")))
	//{
	//	map.Add(TEXT("AGE"), 20);	// KEY = AGE, 값 20
	//}
	//else
	//{
	//	map[TEXT("AGE")] = 20;
	//}
	//int aa = map[TEXT("AGE")];
	//map.Remove(TEXT("AGE"));

	// UE_LOG(LogTemp, Warning, TEXT("Hello World!"));
	// number 출력
	// UE_LOG(LogTemp, Warning, TEXT("%d"), number);
	// UE_LOG(LogTemp, Warning, TEXT("%.2f"), fNumber);

	// int size = sizeof(bReady);
	// UE_LOG(LogTemp, Warning, TEXT("%d"), size);
	// UE_LOG(LogTemp, Warning, TEXT("bool is false : %d"), bReady);
	// UE_LOG(LogTemp, Warning, TEXT("bool is false : %d"), true);
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *myName);

	// 조건문
	// 만약 myName이 KTJ이라면 호주에 별장 사고싶다.
	// 그렇지않고 myName이 LSK이라면 벌금내고싶다.
	// 이도저도 아니라면 맥북사고싶다.

	/*if (myName.Equals(TEXT("KTJ")))
	{
		UE_LOG(LogTemp, Warning, TEXT("호주에 별장 사고싶다."));
	}
	else if (myName.Equals(TEXT("LSK")))
	{
		UE_LOG(LogTemp, Warning, TEXT("벌금내고 싶다."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("맥북 사고싶다."));
	}*/

	// 반복문
	// 0부터 100까지 반복문에서
	// - 짝수만 출력
	// int a = 0;
	/*for (int i = 0; i <= 100; i++)
	{
		if (i >= 50 && i <= 60)
			UE_LOG(LogTemp, Warning, TEXT("%d"), i);
	}*/
}

// Called every frame
void ACodingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 1. tick에서 시간이 흐르다가 
	currentTime += DeltaTime;
	// 2. noteIndex가 배열크기보다 작고 배열의 현재 인덱스 항목의 시간만큼 시간이 흘렀다면 
	if (noteIndex < notes.Num() && currentTime >= notes[noteIndex])
	{
		// 3. 배열의 인덱스와 값을 출력하고 인덱스값을 1 증가
		UE_LOG(LogTemp, Warning, TEXT("index : %d, time : %.2f"), noteIndex, notes[noteIndex]);

		noteIndex++;
	}
}

// 함수의 정의/구현
int ACodingActor::MyAdd(int a, int b)
{
	return a + b;
}

int ACodingActor::MyAdd2(int a, int b)
{
	return a + b;
}

int ACodingActor::MyAdd4_Implementation(int a, int b)
{
	return a + b;
}

AActor* ACodingActor::GetTestValue()
{
	static bool b = false;
	if (false == b)
	{
		b = true;
		test1.Add(this);
		test2.Add(test1);

	}
	
	return test2[0][0];
}

