// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "UnitProperty.h"
#include "Unit.h"
#include "Tower.generated.h"



UCLASS()
class GXLM_API ATower : public AUnit
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATower();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "UnitPropery")
	UUnitProperty* UnitProperty;
private:
	//HealthBarElement* pHealthBarElement;
};

typedef TArray<ATower*>* EnemyTowersRef;