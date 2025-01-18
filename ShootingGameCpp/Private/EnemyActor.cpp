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

	// box의 모양을 만들고싶다.
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	// 박스를 RootComponent로 하고싶다.
	SetRootComponent(box);
	box->SetBoxExtent(FVector(50));

	// 외관을 만들고싶다.
	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cube"));

	auto cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"));

	// 만약 파일 로딩 성공여부 확인해서 성공했다면
	if (cubeMesh.Succeeded())
	{
		// cube에 mesh를 넣어줘야함
		cube->SetStaticMesh(cubeMesh.Object);

		// (Pitch = 0.000000, Yaw = 0.000000, Roll = 0.000000)
		cube->SetRelativeRotation(FRotator(0, 0, 0));
		// (X=1.000000,Y=1.000000,Z=0.250000)
		cube->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.25f));
	}

	// 외관을 Root에 붙이고싶다. (Attach)
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
	// 태어날 때 방향을 정하고싶다.
	// 30% 확률로는 플레이어를 향하는 방향, 나머지 확률로는 앞방향으로 하고싶다.

	// 확률을 구하고싶다.
	int32 randValue = FMath::RandRange(0, 9);
	// 만약 30%라면
	if (randValue < 3)
	{
		//	플레이어 폰을 찾고싶다.
		for (TObjectIterator<APlayerPawn> it; it; ++it)
		{
			APlayerPawn* target = *it;
			if (target == nullptr)
				continue;
			//	플레이어폰을 향하는 방향을 구해서 기억하고싶다.
			direction = target->GetActorLocation() - GetActorLocation();
				//	그 방향이 크기를 1로 만들고싶다.
			direction.Normalize();
			break;
		}
	}
	// 그렇지 않다면
	else
	{
		// 앞 방향을 기억 하고싶다.
		direction = GetActorForwardVector();
	}

	// box에게 충돌했으면 나도 알려줘라고 하고싶다.
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
	// 상대방이 Player라면
	APlayerPawn* player = Cast<APlayerPawn>(OtherActor);
	if (nullptr == player)
		return;

	// 플레이어의 체력을 1 감소하고싶다.
	player->OnDamageProcess(1);
	// 만약 플레이어의 체력이 0이하라면 파괴하고싶다.
	if (player->hp <= 0)
	{
		// 너죽고
		player->Destroy();
		// 나죽고 하고싶다.
		// 게임오버 UI를 화면에 보이게 하고싶다.
		auto ui = 
			CreateWidget(GetWorld(), gameOverUIFactory);
		gameOverUI = Cast<UGameOverWidget>(ui);
		gameOverUI->AddToViewport(99);

		auto PlayerController = GetWorld()->GetFirstPlayerController();
		// 일시정지 하고싶다.
		PlayerController->SetPause(true);
		// UGameplayStatics::SetGamePaused(GetWorld(), true);
		// 마우스 커서 보이게 하고싶다.
		PlayerController->SetShowMouseCursor(true);
		// 입력모드를 UI만 하고싶다.
		PlayerController->SetInputMode(FInputModeUIOnly());
	}

	// 나죽고 하고싶다.
	this->Destroy();
	
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSFX);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionVFX, GetActorLocation(), GetActorRotation());
}

