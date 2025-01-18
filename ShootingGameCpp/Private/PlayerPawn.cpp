// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "BulletActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMesh.h"
#include "Components/WidgetComponent.h"
#include "PlayerHPWidget.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// box의 모양을 만들고싶다.
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	// 박스를 RootComponent로 하고싶다.
	SetRootComponent(box);

	// 외관을 만들고싶다.
	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cube"));

	// 파일 로딩 시도
	auto cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Couch.SM_Couch'"));

	// 만약 파일 로딩 성공여부 확인해서 성공했다면
	if (cubeMesh.Succeeded())
	{
		// cube에 mesh를 넣어줘야함
		cube->SetStaticMesh(cubeMesh.Object);

		// (Pitch=90.000000,Yaw=360.000000,Roll=360.000000)
		cube->SetRelativeRotation(FRotator(90, 0, 0));
		// (X=1.000000,Y=0.250000,Z=0.250000)
		cube->SetRelativeScale3D(FVector(1.0f, 0.25f, 0.25f));
	}

	// 외관을 Root에 붙이고싶다. (Attach)
	cube->SetupAttachment(box);

	// arrow를 생성해서 배치하고싶다.
	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("arrow"));
	arrow->SetupAttachment(box);
	// Loc (X=0.000000,Y=0.000000,Z=70.000000)
	arrow->SetRelativeLocation(FVector(0, 0, 70));
	// Rot (Pitch=90.000000,Yaw=0.000000,Roll=0.000000)
	arrow->SetRelativeRotation(FRotator(90, 0, 0));

	static ConstructorHelpers::FClassFinder<ABulletActor> BulletBPClass(TEXT("/Game/Blueprints/BP_BulletActor"));

	if (BulletBPClass.Succeeded())
	{
		bulletFactory = BulletBPClass.Class;
	}

	box->SetGenerateOverlapEvents(true);

	box->SetCollisionProfileName(TEXT("Player"));

	// 플레이어의 체력 UI를 만들어서 붙이고 싶다.
	hpComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("hpComp"));
	
	hpComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	playerHP = Cast<UPlayerHPWidget>(hpComp->GetWidget());
	// 태어날 때 체력을 최대체력으로 하고싶다.
	hp = maxHP;
	// UI에도 반영하고싶다.
	playerHP->SetPercent(hp, maxHP);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move ====================================================
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector dir = GetActorUpVector() * v + GetActorRightVector() * h;
	dir.Normalize();
	FVector velocity = dir * Speed;
	SetActorLocation(P0 + velocity * DeltaTime);
	//=========================================================

	// AutoFire ===============================================
	// 만약 bAutoFire가 true라면
	if (bAutoFire == true)
	{
		// 시간이 흐르다가
		currentTime += DeltaTime;
		// 현재시간이 생성시간이 되면
		if (currentTime > makeTime)
		{
			// MakeBullet 함수를 호출하고싶다.
			MakeBullet();
			// 현재시간을 0으로 초기화 하고싶다.
			currentTime = 0;
		}
	}
	// ========================================================

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// 입력이 발생할 때 호출될 함수를 등록해야한다.

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this,
		&APlayerPawn::AxisHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this,
		&APlayerPawn::AxisVertical);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &APlayerPawn::ActionFirePressed);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Released, this, &APlayerPawn::ActionFireReleased);
}

void APlayerPawn::AxisHorizontal(float value)
{
	h = value;
}

void APlayerPawn::AxisVertical(float value)
{
	v = value;
}

void APlayerPawn::ActionFirePressed()
{
	// 자동총쏘기 활성화 하고싶다.
	bAutoFire = true;
	// 현재시간을 0으로 초기화 하고 싶다.
	currentTime = 0;
	MakeBullet();
}

void APlayerPawn::ActionFireReleased()
{
	// 자동총쏘기 그만 하고싶다.
	bAutoFire = false;
}

void APlayerPawn::MakeBullet()
{
	GetWorld()->SpawnActor<ABulletActor>(bulletFactory, arrow->GetComponentTransform());

	UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
}

void APlayerPawn::OnDamageProcess(int damage)
{
	if (--hp < 0)
	{
		hp = 0;
	}
	// hp = FMath::MAX(hp - 1, 0);
	playerHP->SetPercent(hp, maxHP);
}

