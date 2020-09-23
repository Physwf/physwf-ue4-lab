// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TopDownGameGameMode.h"
#include "TopDownGamePlayerController.h"
#include "TopDownGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATopDownGameGameMode::ATopDownGameGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATopDownGamePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}