// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
 
#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString Name; 
	uint16 MaxPlayers; 
	uint16 CurrentPlayers;
	FString HostUserName;


};




/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void HostServer();
	
	UFUNCTION()
	void OpenJoinMenu();
	
	UFUNCTION()
	void GoBackToMain();

	UFUNCTION()
	void JoinGame();

	UFUNCTION()
	void Quit();


	UFUNCTION()
	void GoToHostMenu();


	TOptional<uint32> SelectedIndex;
	

	


protected:
	virtual bool Initialize() override;

public:

	void SetServerList(TArray<FServerData> ServerList);


	UMainMenu(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;


	UPROPERTY(meta = (BindWidget))
	class UButton* CancelJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConfirmJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostMenuCancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConfirmHostButton;


	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* HostNameEditBox;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;
	
	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu;




	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;


	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;


	
	TSubclassOf<class UUserWidget> ServerLineWidgetClass;

	/*UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPAddressField;*/


	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ServerBrowser;
	
	
	void SelectIndex(uint32 Index);


	void UpdateChildren();

};
