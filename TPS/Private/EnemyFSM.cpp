// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "TPSPlayer.h"
#include "Enemy.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	// �¾ �� Enemy�� ����ϰ�ʹ�.
	Me = Cast<AEnemy>(GetOwner());
	
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// �� ���¿� ���� ���� ���� ó���ϰ� �ʹ�.
	switch (State)
	{
	case EEnemyState::Idle:
		TickIdle();
		break;
	case EEnemyState::Move:
		TickMove();
		break;
	case EEnemyState::Attack:
		TickAttack();
		break;
	case EEnemyState::Damage:
		TickDamage();
		break;
	case EEnemyState::Die:
		TickDie();
		break;
	}

}

void UEnemyFSM::TickIdle()
{
	// �÷��̾ ã�� �������� ����ϰ�ʹ�.
	Target = Cast<ATPSPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// ���� ã�Ҵٸ�
	if (Target)
	{
		// �̵����·� �����ϰ�ʹ�.
		SetState(EEnemyState::Move); // ����
	}
}

void UEnemyFSM::TickMove()
{
	// �������� ���ؼ� �̵��ϰ�ʹ�.
	FVector dir = Target->GetActorLocation() - Me->GetActorLocation();
	// dir.Normalize();

	Me->AddMovementInput(dir.GetSafeNormal());
	// ���� ���� ���ɰŸ����
	if (dir.Size() <= AttackDistance)
	{
		// ���� ���·� �����ϰ�ʹ�.
		SetState(EEnemyState::Attack);
	}
}

void UEnemyFSM::TickAttack()
{
	
}

void UEnemyFSM::TickDamage()
{
	// �ð��� �帣�ٰ�
	CurrentTime += GetWorld()->GetDeltaSeconds();
	// ����ð��� DamageTime�� �ʰ��ϸ�
	if (CurrentTime > DamageTime)
	{
		// �̵����·� �����ϰ�ʹ�.
		SetState(EEnemyState::Move);
	}
}

void UEnemyFSM::TickDie()
{
	// �ð��� �帣�ٰ�
	CurrentTime += GetWorld()->GetDeltaSeconds();
	// ����ð��� DieTime�� �ʰ��ϸ�
	if (CurrentTime > DieTime)
	{
		// �ı��ǰ�ʹ�.
		Me->Destroy();
	}
	else
	{
		// �ٴ����� �������� �ʹ�.
		// P = P0 + vt;
		//FVector P0 = Me->GetActorLocation();
		//FVector velocity = FVector::DownVector * 200;
		//FVector vt = velocity * GetWorld()->GetDeltaSeconds();
		//Me->SetActorLocation(P0 + vt);
		
		// ��������
		// ���� Me->GetActorLocation()
		// �� DieEndLoc
		// t : ds * 6 

		FVector NewLoc = FMath::Lerp<FVector>(Me->GetActorLocation(), DieEndLoc, GetWorld()->GetDeltaSeconds() * 2);

		Me->SetActorLocation(NewLoc);
	}
}

void UEnemyFSM::OnTakeDamage(int32 damage)
{
	// �������� �Ծ����� ü���� 1 �����ϰ�ʹ�.
	HP -= damage;
	// ü���� 0���� ũ�� ������ ���·� �����ϰ�ʹ�.
	if (HP > 0)
	{
		// ������ ���·� �����ϰ�ʹ�.
		SetState(EEnemyState::Damage);
	}
	// �׷��� �ʰ� ü���� 0 ���϶�� ���� ���·� �����ϰ�ʹ�.
	else
	{
		// ���� ���·� �����ϰ�ʹ�.
		SetState(EEnemyState::Die);
		// �ٴڰ� �浹���� �ʰ� �浹������ ����ʹ�.
		Me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		DieEndLoc = Me->GetActorLocation() + FVector::DownVector * 200;
	}
}

void UEnemyFSM::SetState(EEnemyState next)
{
	State = next;
	CurrentTime = 0;
}

