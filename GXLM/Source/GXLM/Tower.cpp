// Fill out your copyright notice in the Description page of Project Settings.

#include "GXLM.h"
#include "Tower.h"
#include "UIManager.h"

// Sets default values
ATower::ATower()
{
	
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	//pHealthBarElement = HealthBarElement::Create(10, 80, 0xFF0000, this);
	//pHealthBarElement->OnHealthChange(0, 50, 100);
	//HeathBar->AddElement(pHealthBarElement->Material, NULL, false, (float)pHealthBarElement->BaseSizeX, (float)pHealthBarElement->BaseSizeY, NULL);
	
	//UIManager::GetHealthBarMgr()->CreateHealthBar(GetName(), HealthBarType::OurHero);
	//UIManager::GetHealthBarMgr()->ShowHealthBar(GetName());
}

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//FVector ActorLocation = GetActorLocation();
	//UIManager::GetHealthBarMgr()->UpdateHealthBar(GetName(), ActorLocation);
}

