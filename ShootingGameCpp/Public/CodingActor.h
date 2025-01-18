// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodingActor.generated.h"

UCLASS()
class SHOOTINGGAMECPP_API ACodingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	// (Edit / Visible) + (Anywhere / DefaultsOnly / InstanceOnly)
	// Visible + Anywhere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = myVar);
	// int = long int
	int number = 10; // 4 byte 정수형
	//long long aa = 10; // 8 byte 정수형
	//char c = 10; // 1byte 정수형
	//short int ccc = 10; // 2 byte 정수형

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = myVar);
	float fNumber = 10.0F; // 실수형

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = myVar);
	bool bReady = false; // 논리형

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = myVar);
	FString myName = TEXT("KTJ"); // 문자열

	// 노트 배열 만들고 BeginPlay에서 값을 채우고 Tick에서 시간의 진행에 따라 배열 값을 출력하고싶다.
	TArray<float> notes;
	int noteIndex;
	float currentTime;

	
	UFUNCTION(BlueprintCallable)
	int MyAdd(int a, int b);	// 함수의 선언

	UFUNCTION(BlueprintPure)
	int MyAdd2(int a, int b);	// 함수의 선언

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	int MyAdd3(int a, int b);	// 함수의 선언

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int MyAdd4(int a, int b);	// 함수의 선언

	TArray<AActor*> test1;
	TArray<TArray<AActor*>> test2;

	UFUNCTION(BlueprintCallable)
	AActor* GetTestValue();

};