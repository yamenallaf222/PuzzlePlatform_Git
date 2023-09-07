// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerlineUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UServerlineUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void OnServerClicked();


	UPROPERTY()
	class UMainMenu* ParentMenu;
	
	
	uint32 IndexToSelect;

public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;
	
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HostUserName;


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ConnectionFraction;

	UPROPERTY(meta = (BindWidget))
	class UButton* ServerLineButton;



	UPROPERTY(VisibleAnywhere , BlueprintReadOnly)
	bool bIsSelected = false;




	void Setup(class UMainMenu* Parent, uint32 Index);
	
};
