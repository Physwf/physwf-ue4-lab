// Fill out your copyright notice in the Description page of Project Settings.

#include "GXLM.h"
#include "UnitProperty.h"


// Sets default values
UUnitProperty::UUnitProperty()
{
	Alliance = EAliance::None;
	Health = MaxHealth;
}

void UUnitProperty::AddHealth(int32 amount)
{
	Health += amount;
	Health = FMath::Max(Health, MaxHealth);
}

void UUnitProperty::LoseHealth(int32 amount)
{
	Health -= amount;
	Health = FMath::Min(Health, 0);
}