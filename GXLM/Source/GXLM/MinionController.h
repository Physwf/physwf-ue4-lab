// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "MinionController.generated.h"

/**
 * 
 */
UCLASS()
class GXLM_API AMinionController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
};
