// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "MovingPlatform.h"
// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));

	if (!ensure(TriggerVolume != nullptr)) return;
	
	RootComponent = TriggerVolume;


	

	
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnBeginOverlap);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnEndOverlap);
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (AMovingPlatform* MovingPlatform : PlatformsToTrigger)
	{
		if (!ensure(!(MovingPlatform != nullptr)))
		return;

		MovingPlatform->AddActiveTrigger();
	}

	UE_LOG(LogTemp, Warning, TEXT("Activated"));
}


void APlatformTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	 int32 OtherBodyIndex)
{
	for (AMovingPlatform* MovingPlatform : PlatformsToTrigger)
	{
		if (!ensure(!(MovingPlatform != nullptr)))
		{
			return;
		}
		MovingPlatform->RemoveActiveTrigger();
	}
	UE_LOG(LogTemp, Warning, TEXT("Deactivated"));
}