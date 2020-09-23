// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "UnitProperty.generated.h"

UENUM(BlueprintType)
enum class EAliance : uint8
{
	None UMETA(DisplayName = "None"),
	Neutral UMETA(DisplayName = "Neutral"),
	Red  UMETA(DisplayName="Red"),
	Blue UMETA(DisplayName = "Blue")
};

UENUM(BlueprintType)
enum class EUnitType : uint8
{
	Minion UMETA(DisplayName = "Minion"),
	Hero UMETA(DisplayName = "Hero")
};

UCLASS(Blueprintable, BlueprintType)
class GXLM_API UUnitProperty : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UUnitProperty();

	virtual void AddHealth(int32 amount);
	virtual void LoseHealth(int32 amount);
	FORCEINLINE virtual int32 GetHealth()const { return Health; }
	FORCEINLINE virtual bool IsDead() const{ return Health <= 0; }
	
	FORCEINLINE virtual bool IsEnemy(UUnitProperty& InUnit) const { return InUnit.Alliance != Alliance; }

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Propery")
	int32 MaxHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Propery")
	float UnitSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Propery")
	EAliance Alliance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Propery")
	EUnitType Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	bool IsAttacking;
private:
	int32 Health;


};
