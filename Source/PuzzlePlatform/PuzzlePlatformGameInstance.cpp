// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"
#include "Engine/Engine.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "UObject/ConstructorHelpers.h"
#include "MenuSystem/MainMenu.h"


#define validate(X) if(!ensure(X!=nullptr)) return;

const static FName SESSION_NAME = NAME_GameSession;

void UPuzzlePlatformGameInstance::Init()
{

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	UE_LOG(LogTemp, Warning, TEXT("Online Subsystem Name : %s"), *OnlineSubsystem->GetSubsystemName().ToString());


	

	if (OnlineSubsystem != nullptr)
	{
		SessionInterface = OnlineSubsystem->GetSessionInterface();
	}

	if (SessionInterface.IsValid())
	{
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnCreateSessionComplete);
		SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnDestroySessionComplete);
		SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnFindSessionsComplete);
		SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnJoinSessionComplete);


	}
	//UE_LOG(LogTemp, Warning, TEXT("Found Class : %s"), *MainMenuWidget->GetName());
}

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer &ObjectInitializer)
{
	
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/UI/WBP_MainMenu"));
	validate(MainMenuBPClass.Class);
	MainMenuWidget = MainMenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/UI/WBP_InGameMenu"));
	validate(InGameMenuBPClass.Class);
	InGameMenuWidget = InGameMenuBPClass.Class;

	
	
	
	//UE_LOG(LogTemp, Warning, TEXT("Found Class : %s"), *PlatformTriggerBPClass.Class->GetName());
}


void UPuzzlePlatformGameInstance::Host(FString HostName)
{
	
	HostNameSaved = HostName;
	if (SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		
		if (ExistingSession == nullptr)
		{
			CreateSession();
		}

		else
		{
			
			
			SessionInterface->DestroySession(SESSION_NAME);

		}


	}

}


void UPuzzlePlatformGameInstance::InGameLoadMenu()
{
	validate(InGameMenuWidget);
	UMenuWidget* InGameMenu = CreateWidget<UMenuWidget>(this, InGameMenuWidget);

	validate(InGameMenu);

	InGameMenu->Setup();
	InGameMenu->SetMenuInterface(this);
}


void UPuzzlePlatformGameInstance::LoadMenu()
{

	validate(MainMenuWidget);

	MainMenu = CreateWidget<UMainMenu>(this, MainMenuWidget);

	validate(MainMenu);


	MainMenu->Setup();

	MainMenu->SetMenuInterface(this);


}

void UPuzzlePlatformGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	
	if (SessionSearch.IsValid())
	{
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		UE_LOG(LogTemp, Warning, TEXT("Starting Search For Online Sessions....."));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
	
}



void UPuzzlePlatformGameInstance::Join(uint32 Index)
{
	
	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;

	

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
}


void UPuzzlePlatformGameInstance::GoBackToMainMenu()
{
	
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	validate(PlayerController);

	PlayerController->ClientTravel("/Game/UI/MainMenuLevel", TRAVEL_Absolute);
}


void UPuzzlePlatformGameInstance::QuitGame()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	validate(PlayerController);

	PlayerController->ConsoleCommand(TEXT("quit"));
}






void UPuzzlePlatformGameInstance::OnCreateSessionComplete(FName SessionName , bool bWasSuccessful)
{

	UEngine* Engine = GetEngine();
	if (bWasSuccessful)
	{
		if (Engine != nullptr)

			Engine->AddOnScreenDebugMessage(0, 0.f, FColor::Green, TEXT("fucking hosting and session creatin went rocketing"));



		UWorld* World = GetWorld();

		if (!ensure(World != nullptr))return;


		World->ServerTravel("/Game/PuzzlePlatform/Maps/Lobby?listen");
	}

	else
	{
		if (Engine != nullptr)

			Engine->AddOnScreenDebugMessage(0, .5f, FColor::Green, TEXT("fuck internet it always go down and prevents us being happy in a session"));
	}

	
}



void UPuzzlePlatformGameInstance::OnDestroySessionComplete(FName SessionName , bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		CreateSession();
	}
}


void UPuzzlePlatformGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings OnlineSessionSettings;
		
		


		OnlineSessionSettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
		OnlineSessionSettings.NumPublicConnections = 3;
		OnlineSessionSettings.bShouldAdvertise= true;
		OnlineSessionSettings.bUsesPresence = true;
		OnlineSessionSettings.bUseLobbiesIfAvailable = true; 
		OnlineSessionSettings.Set(TEXT("DisplayedServerName"), HostNameSaved, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);



		SessionInterface->CreateSession(0, SESSION_NAME, OnlineSessionSettings);
	}
}



void UPuzzlePlatformGameInstance::FireUpSession()
{
	SessionInterface->StartSession(SESSION_NAME);
}


void UPuzzlePlatformGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		FOnlineSessionSearch* OnlineSessionSearch = SessionSearch.Get();
		if (OnlineSessionSearch != nullptr)
		{
			TArray<FOnlineSessionSearchResult> OnlineSessionSearchResults = OnlineSessionSearch->SearchResults;
			validate(MainMenu);

			if(OnlineSessionSearchResults.IsEmpty())
			{ 
				UE_LOG(LogTemp, Warning, TEXT("Session Find Process Completed with zero Session"))
				

			}
			
			else
			{

				TArray<FServerData> ServersData;
				FString OnlineSessionsFoundString = FString::Printf(TEXT("Session Find Process Completed with  %d Sessions Found: "), OnlineSessionSearchResults.Num());;
				for (const FOnlineSessionSearchResult& OnlineSessionResult : OnlineSessionSearchResults)
				{
					OnlineSessionsFoundString +=  "    " + OnlineSessionResult.Session.OwningUserName;
					
					FServerData ServerData;

					FString ServerNameDisplayed;


					if (OnlineSessionResult.Session.SessionSettings.Get(TEXT("DisplayedServerName"), ServerNameDisplayed))
					{
						ServerData.Name = ServerNameDisplayed;
					}

					else
					{
						ServerData.Name = "Could Not Find Name.";
					}

					ServerData.HostUserName = OnlineSessionResult.Session.OwningUserName;
					ServerData.MaxPlayers = OnlineSessionResult.Session.SessionSettings.NumPublicConnections;
					ServerData.CurrentPlayers = ServerData.MaxPlayers - OnlineSessionResult.Session.NumOpenPublicConnections;
					
					ServersData.Add(ServerData);
				}

				MainMenu->SetServerList(ServersData);
				UE_LOG(LogTemp, Warning,TEXT("%s"), *OnlineSessionsFoundString);

			}
		}



	}



	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Session Find Process went Down for unexpected shit"));
	}

}



void UPuzzlePlatformGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{

	if (!SessionInterface.IsValid()) return;

	

	
	UEngine* Engine = GetEngine();

	if (!ensure(Engine != nullptr)) return;

	FString ConnectInfo;

	if (!SessionInterface->GetResolvedConnectString(SessionName, ConnectInfo))
	{	
		Engine->AddOnScreenDebugMessage(0, 3.0f, FColor::Yellow, FString::Printf(TEXT("Could not get connect String ")));
	}
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	validate(PlayerController);


	PlayerController->ClientTravel(ConnectInfo, TRAVEL_Absolute);

	Engine->AddOnScreenDebugMessage(0, 3.0f, FColor::Green, FString::Printf(TEXT("Joining...\nHere is your IP %s"), *ConnectInfo));



}