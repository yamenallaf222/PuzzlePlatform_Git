// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PuzzlePlatformGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UPuzzlePlatformGameInstance : public UGameInstance , public IMenuInterface
{
	GENERATED_BODY()


private:
	TSubclassOf<class UUserWidget> MainMenuWidget;
	TSubclassOf<class UUserWidget> InGameMenuWidget;
	class UMainMenu* MainMenu;
	IOnlineSessionPtr SessionInterface;
	FTimerHandle StartSessionTimerHandle;
	
	FString HostNameSaved;

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;


	void OnFindSessionsComplete(bool bWasSuccessful);

	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);


	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type);

public:


	void FireUpSession();



	UPuzzlePlatformGameInstance(const FObjectInitializer &ObjectInitializer);
	
	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void InGameLoadMenu();


	UFUNCTION(Exec)
	void Host(FString HostName)override;

	UFUNCTION(Exec)
	void Join(uint32 Index)override;


	UFUNCTION()
	virtual void GoBackToMainMenu()override;

	virtual void RefreshServerList() override;





	void QuitGame();



	void CreateSession();

	
};
