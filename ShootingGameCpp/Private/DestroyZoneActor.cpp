// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyZoneActor.h"
#include "Components/BoxComponent.h"

// Sets default values
ADestroyZoneActor::ADestroyZoneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	SetRootComponent(box);
	box->SetBoxExtent(FVector(50, 50, 50));

	box->SetCollisionProfileName(TEXT("DestroyZone"));

	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cube"));
	cube->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADestroyZoneActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroyZoneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyZoneActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	// 상대를 파괴하고 싶다.
	OtherActor->Destroy();
}


