// Fill out your copyright notice in the Description page of Project Settings.


#include "TailActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.h"

// Sets default values
ATailActor::ATailActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	SetRootComponent(box);

	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cube"));
	cube->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATailActor::BeginPlay()
{
	Super::BeginPlay();
	// 만약 target이 nullptr이라면 target에 플레이어폰을 찾아서 넣어주고싶다.

	// UGameplayStatics::GetPlayerPawn
	// UGameplayStatics::GetActorofClass
	// UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass());
	// GetWorld()->GetFirstPlayerController()->GetPawn()
	if (targetActor == nullptr)
	{
		targetActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	}
}

// Called every frame
void ATailActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// target - me 로 방향을 만들고
	FVector dir = targetActor->GetActorLocation() - this->GetActorLocation();
	dir.Normalize();
	// 그 방향으로 이동하고싶다
	SetActorLocation(GetActorLocation() + dir * Speed * DeltaTime);
}

