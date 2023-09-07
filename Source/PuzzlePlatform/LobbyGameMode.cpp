// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "PuzzlePlayerController.h"
#include "PuzzlePlatformGameInstance.h"



//void AActualGameMode::LogTheFuckingThing()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Players Crossed %d"), ControllersPassedTheLine.Num()));
//
//}
//
//void AActualGameMode::AddToControllersPassed(AController* PlayerController)
//{
//	for (AController* Controller : ControllersPassedTheLine)
//	{
//		if (Controller == PlayerController) return;
//	}
//
//	ControllersPassedTheLine.Add(PlayerController);
//}
//
//
//void AActualGameMode::EndGame(bool bAreWinners)
//{	
//	if (HasAuthority())
//	{
//		if (ControllersPassedTheLine.Num() == GetWorld()->GetNumPlayerControllers())
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString(TEXT("Horray i Ended the game")));
//
//			for (AController* Controller : ControllersPassedTheLine)
//			{
//				APuzzlePlayerController* PuzzlePlayerController = Cast<APuzzlePlayerController>(Controller);
//
//				if (!ensure(PuzzlePlayerController != nullptr)) return;
//
//				PuzzlePlayerController->GameHasEnded(PuzzlePlayerController->GetPawn(), bAreWinners);
//
//				
//			}
//		}
//
//	}
//}
//





void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{

	Super::PostLogin(NewPlayer);


	++PlayersInLobbyCount;

	if (PlayersInLobbyCount >= 2)
	{
		UWorld* World = GetWorld();
		
		if (World)
		{
			
			World->GetTimerManager().SetTimer(StartSessionTimerHandle, this, &ALobbyGameMode::FireUpSession, 10.f);

		}
	}

}



void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	--PlayersInLobbyCount;
}



void ALobbyGameMode::FireUpSession()
{
	UPuzzlePlatformGameInstance* GameInstance = Cast<UPuzzlePlatformGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Aint no starting session"));
		GameInstance->FireUpSession();
	}

	bUseSeamlessTravel = true;
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	World->ServerTravel("/Game/PuzzlePlatform/Maps/GameMap");


}


