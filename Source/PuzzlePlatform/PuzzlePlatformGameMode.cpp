// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzlePlatformGameMode.h"






APuzzlePlatformGameMode::APuzzlePlatformGameMode()
{
	ConstructorHelpers::FClassFinder <APawn> DefaultPawnFinder(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));

	if (DefaultPawnFinder.Class != nullptr)
		DefaultPawnClass = DefaultPawnFinder.Class;


}

