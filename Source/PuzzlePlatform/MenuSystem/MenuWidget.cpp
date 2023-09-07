// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterfacePassed)
{
	this->MenuInterface = MenuInterfacePassed;
	
}



void UMenuWidget::Setup()
{
	this->AddToViewport();

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;


	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;

	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);


	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;

}


void UMenuWidget::TearDown()
{


	this->RemoveFromViewport();

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr)) return;


	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->SetInputMode(FInputModeGameOnly{});

	PlayerController->bShowMouseCursor = false;

}


void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);


	TearDown();

}