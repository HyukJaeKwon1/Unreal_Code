// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "EngineUtils.h"
#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameOverWidget.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// box�� ����� �����ʹ�.
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	// �ڽ��� RootComponent�� �ϰ�ʹ�.
	SetRootComponent(box);
	box->SetBoxExtent(FVector(50));

	// �ܰ��� �����ʹ�.
	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cube"));

	auto cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"));

	// ���� ���� �ε� �������� Ȯ���ؼ� �����ߴٸ�
	if (cubeMesh.Succeeded())
	{
		// cube�� mesh�� �־������
		cube->SetStaticMesh(cubeMesh.Object);

		// (Pitch = 0.000000, Yaw = 0.000000, Roll = 0.000000)
		cube->SetRelativeRotation(FRotator(0, 0, 0));
		// (X=1.000000,Y=1.000000,Z=0.250000)
		cube->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.25f));
	}

	// �ܰ��� Root�� ���̰�ʹ�. (Attach)
	cube->SetupAttachment(RootComponent);

	box->SetGenerateOverlapEvents(true);

	box->SetCollisionProfileName(TEXT("Enemy"));

	//ConstructorHelpers::FObjectFinder<UParticleSystem> temp(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));

	//if (temp.Succeeded())
	//{
	//	explosionVFX = temp.Object;
	//}
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	// �¾ �� ������ ���ϰ�ʹ�.
	// 30% Ȯ���δ� �÷��̾ ���ϴ� ����, ������ Ȯ���δ� �չ������� �ϰ�ʹ�.

	// Ȯ���� ���ϰ�ʹ�.
	int32 randValue = FMath::RandRange(0, 9);
	// ���� 30%���
	if (randValue < 3)
	{
		//	�÷��̾� ���� ã��ʹ�.
		for (TObjectIterator<APlayerPawn> it; it; ++it)
		{
			APlayerPawn* target = *it;
			if (target == nullptr)
				continue;
			//	�÷��̾����� ���ϴ� ������ ���ؼ� ����ϰ�ʹ�.
			direction = target->GetActorLocation() - GetActorLocation();
				//	�� ������ ũ�⸦ 1�� �����ʹ�.
			direction.Normalize();
			break;
		}
	}
	// �׷��� �ʴٸ�
	else
	{
		// �� ������ ��� �ϰ�ʹ�.
		direction = GetActorForwardVector();
	}

	// box���� �浹������ ���� �˷����� �ϰ�ʹ�.
	box->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnBoxCompBeginOverlap);
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector velocity = direction * speed;
	SetActorLocation(P0 + velocity * DeltaTime);
}

void AEnemyActor::OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ������ Player���
	APlayerPawn* player = Cast<APlayerPawn>(OtherActor);
	if (nullptr == player)
		return;

	// �÷��̾��� ü���� 1 �����ϰ�ʹ�.
	player->OnDamageProcess(1);
	// ���� �÷��̾��� ü���� 0���϶�� �ı��ϰ�ʹ�.
	if (player->hp <= 0)
	{
		// ���װ�
		player->Destroy();
		// ���װ� �ϰ�ʹ�.
		// ���ӿ��� UI�� ȭ�鿡 ���̰� �ϰ�ʹ�.
		auto ui = 
			CreateWidget(GetWorld(), gameOverUIFactory);
		gameOverUI = Cast<UGameOverWidget>(ui);
		gameOverUI->AddToViewport(99);

		auto PlayerController = GetWorld()->GetFirstPlayerController();
		// �Ͻ����� �ϰ�ʹ�.
		PlayerController->SetPause(true);
		// UGameplayStatics::SetGamePaused(GetWorld(), true);
		// ���콺 Ŀ�� ���̰� �ϰ�ʹ�.
		PlayerController->SetShowMouseCursor(true);
		// �Է¸�带 UI�� �ϰ�ʹ�.
		PlayerController->SetInputMode(FInputModeUIOnly());
	}

	// ���װ� �ϰ�ʹ�.
	this->Destroy();
	
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSFX);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionVFX, GetActorLocation(), GetActorRotation());
}

