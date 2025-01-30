// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle	 UMETA(DisplayName = "IDLE"),
	Move	 UMETA(DisplayName = "MOVE"),
	Attack	 UMETA(DisplayName = "ATTACK"),
	Damage	 UMETA(DisplayName = "DAMAGE"),
	Die		 UMETA(DisplayName = "DIE"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EEnemyState State;

	UPROPERTY()
	class AEnemy* Me;

	UPROPERTY()
	class ATPSPlayer* Target;

	// ���� ���� �Ÿ�
	float AttackDistance = 200;

	void TickIdle();
	void TickMove();
	void TickAttack();
	void TickDamage();
	void TickDie();

public:
	// �������� �Ծ����� ü���� 1 �����ϰ�ʹ�.
	// ü���� 0���� ũ�� ������ ���·� �����ϰ�ʹ�.
	// �׷��� �ʰ� ü���� 0 ���϶�� ���� ���·� �����ϰ�ʹ�.
	int32 HP = 2;
	void OnTakeDamage(int32 damage);
	void SetState(EEnemyState next);

	float CurrentTime;
	float DamageTime = 2;
	float DieTime = 2;

	// �׾��� �� ������ �������� ���ϰ� �ʹ�.
	FVector DieEndLoc;
};
