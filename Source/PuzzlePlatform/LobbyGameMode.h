// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzlePlatformGameMode.h"
#include "LobbyGameMode.generated.h"
UCLASS()
class PUZZLEPLATFORM_API ALobbyGameMode : public APuzzlePlatformGameMode
{

	GENERATED_BODY()
		//
		//public:
		//
		//	void LogTheFuckingThing();
		//
		//	void AddToControllersPassed(AController* PlayerController);
		//	void EndGame(bool bAreWinners);
		//private:
		//	TArray<AController*> ControllersPassedTheLine;
private:
		uint32 PlayersInLobbyCount = 0;
		FTimerHandle StartSessionTimerHandle;

		void FireUpSession();
		
public:
	void PostLogin(APlayerController* NewPlayer) override;
	void Logout(AController* Exiting) override;

};
