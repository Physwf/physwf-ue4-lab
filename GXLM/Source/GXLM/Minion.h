// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFrameWork/Actor.h"
#include "UnitProperty.h"
#include "Unit.h"
#include "Tower.h"
#include "Minion.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Minion_LOG, Log, All);

/**
 * 
 */
UCLASS()
class GXLM_API AMinion : public AUnit
{
	GENERATED_BODY()
public:
	AMinion();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "UnitPropery")
	UUnitProperty* UnitProperty;

	EnemyTowersRef EnemyTowers;

	UFUNCTION(BlueprintCallable, Category = "AI")
	ATower* GetNearestTower();
};
