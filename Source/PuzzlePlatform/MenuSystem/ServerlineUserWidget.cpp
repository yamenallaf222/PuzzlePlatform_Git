// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerlineUserWidget.h"
#include "Components/Button.h"
#include "MainMenu.h"



void UServerlineUserWidget::Setup(class UMainMenu* Parent, uint32 Index)
{
	IndexToSelect = Index;

	ParentMenu = Parent;

	ServerLineButton->OnClicked.AddDynamic(this,&UServerlineUserWidget::OnServerClicked);
}



void UServerlineUserWidget::OnServerClicked()
{
	if(ParentMenu != nullptr)
		ParentMenu->SelectIndex(IndexToSelect);

}




