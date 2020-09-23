// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "GXLMGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GXLM_API UGXLMGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FString GetSummnoerName() { return SummnoerName; }
	UFUNCTION(BlueprintCallable,Category="GXLM")
	void SetSummnoerName(const FString InName) { SummnoerName = InName; }
private:
	FString SummnoerName;
	
};
