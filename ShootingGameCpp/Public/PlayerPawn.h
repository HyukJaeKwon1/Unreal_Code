// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

// class UBoxComponent; // 전방선언 forward declaration

UCLASS()
class SHOOTINGGAMECPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* cube;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* box; // 포인터 변수 선언시 class의 의미는 전방선언이다.

	UPROPERTY(EditAnywhere)
	class UArrowComponent* arrow;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABulletActor> bulletFactory;

	UPROPERTY(EditAnywhere)
	USoundBase* fireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 500.f;

	float h, v = 0;

	void AxisHorizontal(float value);
	void AxisVertical(float value);

	// 자동 총쏘기 기능을 만들고싶다.
	// - 기능 : 눌렀다, 땟다, 총알을 만든다
	// - 속성 : 누른상태, 현재시간, 총알이 발사되는 시간(인터벌)
	bool bAutoFire;
	float currentTime;
	float makeTime = 0.5f;

	void ActionFirePressed();
	void ActionFireReleased();

	void MakeBullet();

	// 플레이어의 체력 UI를 만들어서 붙이고 싶다.
	// 위젯 컴포넌트
	UPROPERTY(EditAnywhere)
	class UWidgetComponent* hpComp;

	UPROPERTY()
	class UPlayerHPWidget* playerHP;

	int hp;

	UPROPERTY(EditAnywhere)
	int maxHP = 10;
	void OnDamageProcess(int damage);
};
