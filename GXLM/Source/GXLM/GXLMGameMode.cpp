// Fill out your copyright notice in the Description page of Project Settings.

#include "GXLM.h"
#include "GXLMGameMode.h"
#include "SummonerController.h"
#include "Summoner.h"

AGXLMGameMode::AGXLMGameMode()
{
	PlayerControllerClass = ASummonerController::StaticClass();

	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClass(TEXT(""));
	DefaultPawnClass = ASummoner::StaticClass();

}

