// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"



AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}





void AMovingPlatform::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (HasAuthority() && ActiveTriggers > 0)
	{
		MovePlatform(DeltaTime);
	}

	

}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	MinNetUpdateFrequency = 60.f;
	NetUpdateFrequency = 60.f;

	GlobalStartLocation = GetActorLocation();

	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);


	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
		
	}
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{	
	
	FVector Location = GetActorLocation();
	float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
	float JourneyTravelled = (Location - GlobalStartLocation).Size();
	if (JourneyTravelled > JourneyLength)
	{
		FVector Swap = GlobalStartLocation;
		GlobalStartLocation = GlobalTargetLocation;
		GlobalTargetLocation = Swap;
	}


	FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
	Location+= Speed * Direction * DeltaTime;
	SetActorLocation( Location );	
}


void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;

}


void AMovingPlatform::RemoveActiveTrigger()
{
	ActiveTriggers = FMath::Max(ActiveTriggers - 1, 0);
}


