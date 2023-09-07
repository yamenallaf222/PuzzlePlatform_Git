// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "ServerlineUserWidget.h"
#include "Components/TextBlock.h"


UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerLineBPClass(TEXT("/Game/UI/WBP_ServerLineWidget"));

	if (!ensure(ServerLineBPClass.Class != nullptr)) return;


	ServerLineWidgetClass = ServerLineBPClass.Class;

}





bool UMainMenu::Initialize()
{
	bool bSuccess = Super::Initialize();

	if (!bSuccess) return false;

	if (!ensure(HostButton != nullptr))return false;
	if (!ensure(JoinButton != nullptr))return false;
	if (!ensure(CancelJoinMenuButton != nullptr))return false;
	if (!ensure(ConfirmJoinMenuButton != nullptr))return false;
	if (!ensure(QuitButton != nullptr))return false;
	

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::GoToHostMenu);

	ConfirmHostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	HostMenuCancelButton->OnClicked.AddDynamic(this, &UMainMenu::GoBackToMain);

	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::GoBackToMain);

	ConfirmJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::JoinGame);

	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::Quit);

	
	return true;

}






void UMainMenu::HostServer()
{

	if (HostNameEditBox->GetText().IsEmpty()) return;

	if (MenuInterface != nullptr)
	{

		MenuInterface->Host(HostNameEditBox->GetText().ToString());
	}


}

void UMainMenu::OpenJoinMenu()
{
	
	if (!ensure(MenuSwitcher != nullptr))return;
	if (!ensure(JoinMenu!= nullptr))return;

	MenuSwitcher->SetActiveWidget(JoinMenu);

	if (MenuInterface != nullptr)
	{
		MenuInterface->RefreshServerList();
	}

}


void UMainMenu::GoToHostMenu()
{
	if (!ensure(MenuSwitcher != nullptr))return;

	MenuSwitcher->SetActiveWidget(HostMenu);

}


void UMainMenu::GoBackToMain()
{
	if (!ensure(MenuSwitcher != nullptr))return;
	if (!ensure(MainMenu != nullptr))return;

	MenuSwitcher->SetActiveWidget(MainMenu);



}

void UMainMenu::SetServerList(TArray<FServerData> ServerList)
{
	ServerBrowser->ClearChildren();
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	uint32 i = 0;
	for (const FServerData& ServerData : ServerList)
	{

		UServerlineUserWidget* ServerLine = CreateWidget<UServerlineUserWidget>(World, ServerLineWidgetClass);
		if (!ensure(ServerLine != nullptr)) return;
		ServerLine->ServerName->SetText(FText::FromString(ServerData.Name));
		ServerLine->ConnectionFraction->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), ServerData.CurrentPlayers , ServerData.MaxPlayers)));
		ServerLine->HostUserName->SetText(FText::FromString(ServerData.HostUserName));

		ServerLine->Setup(this, i);

		++i;
		
		
		ServerBrowser->AddChild(ServerLine);

	}
}


void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}

void UMainMenu::UpdateChildren()
{
	
	
	if(ServerBrowser != nullptr)
		for (int i = 0; i < ServerBrowser->GetChildrenCount(); ++i)
		{
			UServerlineUserWidget* ServerLine = Cast<UServerlineUserWidget>(ServerBrowser->GetChildAt(i));
			ServerLine->bIsSelected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
		}


}






void UMainMenu::JoinGame()
{

	if (SelectedIndex.IsSet() && MenuInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index %d") , SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index is not set"));
	}
}


void UMainMenu::Quit()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->QuitGame();
	}
}




