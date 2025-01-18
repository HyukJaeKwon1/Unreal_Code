// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS()
class SHOOTINGGAMECPP_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor)
		override;

	virtual void Destroyed() override;

	UFUNCTION()
	void OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 스마트포인터
	//int* a = new int;
	//int* pA = &a;
	//int* pB = &a;

	//pB = nullptr;

	//pA = nullptr;
	//a = nullptr;

	// TArray<class UBoxComponent*> aa;
	// 충돌체와 외관을 만들고싶다.
	UPROPERTY(EditAnywhere)
	class UBoxComponent* box;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* cube;

	// 앞 방향으로 계속 이동하고싶다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float speed = 1000;

	UPROPERTY(EditAnywhere)
	class USoundBase* explosionSFX;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* explosionVFX;
};
