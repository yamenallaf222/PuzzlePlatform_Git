// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void AddActiveTrigger();

	void RemoveActiveTrigger();

private:

	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;


	UPROPERTY(EditAnywhere)
	float Speed = 5.f;

	UPROPERTY(EditAnywhere , Category = "Target" , meta = (MakeEditWidget = "true"))
	FVector TargetLocation;


	FVector GlobalTargetLocation;

	FVector GlobalStartLocation;

	float SwapDelay = 0;

	void MovePlatform(float DeltaTime);
	
};
