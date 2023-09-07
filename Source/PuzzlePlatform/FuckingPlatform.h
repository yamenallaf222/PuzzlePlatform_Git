// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "FuckingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API AFuckingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AFuckingPlatform();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
