// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "PPCpp.h"
#include "PPCppGameMode.h"
#include "PPCppPlayerController.h"

APPCppGameMode::APPCppGameMode()
{
	// no pawn by default
	DefaultPawnClass = NULL;
	// use our own player controller class
	PlayerControllerClass = APPCppPlayerController::StaticClass();
}
