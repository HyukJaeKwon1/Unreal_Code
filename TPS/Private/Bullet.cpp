// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 충돌체를 루트로하고 반지름을 12.5f으로
	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("collisionComp"));
	SetRootComponent(collisionComp);
	collisionComp->SetSphereRadius(12.5f);
	collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	// 외관을 충돌체에 붙이고 크기를 0.25f
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeScale3D(FVector(0.25f));
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 이동컴포넌트 만들고. 속력설정, 튕김설정
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("movementComp"));
	movementComp->InitialSpeed = 3000.0f;
	movementComp->MaxSpeed = 3000.0f;
	movementComp->bShouldBounce = true;
	movementComp->Bounciness = .3f;

	movementComp->SetUpdatedComponent(collisionComp);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle handle;
	
	// GetWorld()->GetTimerManager().SetTimer(handle, this, &ABullet::KillMySelf, 2);
	GetWorld()->GetTimerManager().SetTimer(handle, FTimerDelegate::CreateLambda(
		[this]()->void {
			// TO DO
			this->Destroy();
		})
		, 2, false);

	//auto lambdaAddFunc = [](int32 a, int32 b)->int { return a + b;  };

	//int32 result = lambdaAddFunc(10, 20);

	//int sum = 0;
	//// [캡처](매개변수)->반환자료형 { 구현	}; 자료형에서 void는 생략가능
	//auto lambdaAddFunc = [&sum](int32 a, int32 b)->void { sum = a + b;  };

	//lambdaAddFunc(10, 20);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void ABullet::KillMySelf()
//{
//	Destroy();
//}
//
