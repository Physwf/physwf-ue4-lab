// Fill out your copyright notice in the Description page of Project Settings.

#include "GXLM.h"
#include "Minion.h"
#include "MinionController.h"

DEFINE_LOG_CATEGORY(Minion_LOG);

AMinion::AMinion()
{
	//AIControllerClass = AMinionController::StaticClass();
}

ATower* AMinion::GetNearestTower()
{
	ATower* Result = NULL;
	float dist = MAX_FLT;
	//UE_LOG(Minion_LOG, Warning, TEXT("EnemyTowers = %d"), EnemyTowers != NULL);
	for (auto Tower : *EnemyTowers)
	{
		float curDist = GetDistanceTo(Tower);
		if (curDist < dist)
		{
			Result = Tower;
			dist = curDist;
			//UE_LOG(Minion_LOG, Warning, TEXT("GetNearestTower"));
		}
	}
	return Result;
}