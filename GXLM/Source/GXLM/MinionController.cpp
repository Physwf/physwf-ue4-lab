// Fill out your copyright notice in the Description page of Project Settings.

#include "GXLM.h"
#include "MinionController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BBMinion.h"



void AMinionController::BeginPlay()
{
	UBlackboardComponent *BBComponent = NewObject<UBlackboardComponent>(this);
	BBComponent->RegisterComponent();

	UBBMinion* BB = NewObject<UBBMinion>(this);
	BBComponent->InitializeBlackboard(*BB);
}
