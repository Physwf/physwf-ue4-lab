// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "UnitProperty.h"
#include "Unit.h"
#include "Tower.h"
#include "Inhibitor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Inhibitor_LOG, Log, All);

UCLASS()
class GXLM_API AInhibitor : public AUnit
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInhibitor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type InReason) override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SpawnMinion();

	UPROPERTY(BlueprintReadWrite, Category = "UnitPropery")
	UUnitProperty* UnitProperty;

	UPROPERTY(BlueprintReadWrite, Category = "UnitPropery")
	TArray<ATower*> EnemyTowers;

private:
	FTimerHandle SpawnMinionTimer;
	UClass* MinionClass;
	TArray<FRotator> SpawnDirections;
	TArray<FVector> SpawnLocations;
};
