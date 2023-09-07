// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Delegates/Delegate.h"
#include "PuzzlePlayerController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDisplayWonWidget);


UCLASS()
class PUZZLEPLATFORM_API APuzzlePlayerController : public APlayerController
{
	GENERATED_BODY()


		APuzzlePlayerController();



};
