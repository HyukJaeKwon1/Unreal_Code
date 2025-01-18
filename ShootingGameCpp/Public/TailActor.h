// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TailActor.generated.h"

UCLASS()
class SHOOTINGGAMECPP_API ATailActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATailActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// [필요요소]
	// - 박스컴포넌트
	UPROPERTY(EditAnywhere)
	class UBoxComponent* box; 
	// - staticMesh컴포넌트
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* cube;
	// - 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 450;
	// - 목적지
	UPROPERTY(EditAnywhere)
	AActor* targetActor;
};
