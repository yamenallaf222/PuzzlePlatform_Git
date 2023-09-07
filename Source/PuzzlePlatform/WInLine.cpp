// Fill out your copyright notice in the Description page of Project Settings.


#include "WInLine.h"
#include "Components/BoxComponent.h"
#include "LobbyGameMode.h"

//#define WON 1
//
//// Sets default values
//AWInLine::AWInLine()
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//	
//	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
//	
//	WinBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
//
//
//	SetRootComponent(Root);
//
//	
//	WinBox->SetupAttachment(Root);
//	WinBox->OnComponentBeginOverlap.AddDynamic(this, &AWInLine::OnOverlapBegin);
//	
//	
//}
//
//// Called when the game starts or when spawned
//void AWInLine::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void AWInLine::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//
//
//void AWInLine::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
//	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (HasAuthority())
//	{
//
//		
//
//		AActualGameMode* ActualGameMode = Cast<AActualGameMode>(GetWorld()->GetAuthGameMode());
//
//		//UE_LOG(LogTemp, Warning, TEXT("I entered the fucking thing"));
//		if (!ensure(ActualGameMode != nullptr)) return;
//		APawn* Pawn = Cast<APawn>(OtherActor);
//		AController* Controller = Pawn->GetController();
//
//		if (!ensure(Controller != nullptr)) return;
//		bool bIsPlayerController = Controller->IsPlayerController();
//
//		
//
//
//		if (bIsPlayerController)
//		{
//			ActualGameMode->AddToControllersPassed(Controller);
//			ActualGameMode->LogTheFuckingThing();
//			//Here is a checking and actually Ending the game no matter what 
//			ActualGameMode->EndGame(WON);
//		}
//
//	}
//	
//}
//
