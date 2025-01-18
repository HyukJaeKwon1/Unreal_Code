// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include "Components/BoxComponent.h"
#include "EnemyActor.h"
#include "Kismet/GameplayStatics.h"
#include "ShootingCppGameModeBase.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체와 외관을 생성하고싶다. 계층구조도 잘 설정하고싶다. 충돌체를 Root로 하고 외관을 Root에 붙이고싶다.

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	SetRootComponent(box);

	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cube"));
	cube->SetupAttachment(RootComponent);
	// 외관의 크기와 충돌체의 크기를 설정하고싶다.
	cube->SetRelativeScale3D(FVector(0.75f, 0.25f, 1));
	box->SetBoxExtent(FVector(37.5f, 12.5f, 50));

	// 충돌설정을 하고싶다.
	box->SetGenerateOverlapEvents(true);

	box->SetCollisionProfileName(TEXT("Bullet"));
	
	//box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//box->SetCollisionObjectType(ECC_GameTraceChannel2);
	//box->SetCollisionResponseToAllChannels(ECR_Ignore);
	//box->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);	// Enemy
	//box->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);	// DestroyZone
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	
	// box에게 충돌한 것이 있으면 알려달라고 하고 싶다.
	box->OnComponentBeginOverlap.AddDynamic(this, &ABulletActor::OnBoxCompBeginOverlap);
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 앞 방향으로 계속 이동하고싶다.
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector v = GetActorForwardVector() * speed;
	SetActorLocation(P0 + v * DeltaTime);
}

void ABulletActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//// 부딪힌 상대가 AEnemyActor라면
	//if (OtherActor->IsA<AEnemyActor>())
	//{
	//	AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	//	// 너죽고
	//	enemy->Destroy();
	//	// 나죽고 하고싶다.
	//	this->Destroy();
	//}
}

void ABulletActor::Destroyed()
{
	// 총알이 실제로 파괴되기 직전에 호출되는 함수.
}

void ABulletActor::OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//부딪힌 상대가 AEnemyActor라면
	if (OtherActor->IsA<AEnemyActor>())
	{
		AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
		// 너죽고
		enemy->Destroy();
		// 나죽고 하고싶다.
		this->Destroy();

		UGameplayStatics::PlaySound2D(GetWorld(), explosionSFX);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionVFX, enemy->GetActorTransform());

		// 총알이 적을 파괴하면 AShootingCppGameModeBase의 AddScore(1)
		auto gmode = Cast<AShootingCppGameModeBase>(GetWorld()->GetAuthGameMode());
		gmode->AddScore(1);
		
	}
}