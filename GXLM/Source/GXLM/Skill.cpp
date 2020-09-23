// Fill out your copyright notice in the Description page of Project Settings.

#include "GXLM.h"
#include "Skill.h"

DEFINE_LOG_CATEGORY(Skill_LOG);

USkill::USkill()
{

}

EExecuteStatus USkill::Execute_Implementation()
{
	return EExecuteStatus::Succeed;
}

EExecuteStatus USkill::ExecuteWithTarget_Implementation(AUnit* InTarget)
{
	return EExecuteStatus::Succeed;
}

EExecuteStatus USkill::ExecuteWithLocation_Implementation(FVector InLocation)
{
	return EExecuteStatus::Succeed;
}

EExecuteStatus USkill::ExecuteWithDirection_Implementation(FRotator InRotator)
{
	return EExecuteStatus::Succeed;
}

EExecuteStatus USkill::Tick_Implementation(float DeltaTime)
{
	return EExecuteStatus::Succeed;
}

bool USkill::IsTargetInRange(AUnit* InTarget, float InRange)
{
	return FVector::Dist(Executor->GetActorLocation(), InTarget->GetActorLocation()) <= InRange;
}

bool USkill::IsTargetInFront(AUnit* InTarget, float Degree)
{
	FVector Dir = InTarget->GetActorLocation() - Executor->GetActorLocation();
	Dir.Normalize();
	FVector Forward = Executor->GetActorForwardVector();
	Forward.Normalize();
	return FVector::DotProduct(Dir, Forward) > FMath::Cos(Degree);
}


USkillSystem::USkillSystem()
{

}

USkill* USkillSystem::SpawnSkill(USkillInfo* InInfo, AUnit* InExecutor)
{
	//static FString SkillDir = TEXT("/Game/BluePrints/Skill/Basic");
	//FString SkillPath = SkillDir + InInfo->Name;
	//LoadObject<UClass>(ANY_PACKAGE, *SkillDir);
	//FindObject<UClass>(ANY_PACKAGE, *SkillDir);
    UE_LOG(Skill_LOG,Warning,TEXT("Spawning Skill: ID:%d,Name:%s"), InInfo->ID, *InInfo->Name);
    /*
	if (USkill** pSkill = SkillCache.Find(InInfo->ID))
	{
		return *pSkill;
	}
	else*/
	{
        UE_LOG(Skill_LOG, Warning, TEXT("Create Skill %s"),*InInfo->Name);
		UClass* SkillClass = LoadObject<UClass>(this, TEXT("/Game/BluePrints/Skill/Basic.Basic_C"));
		if (SkillClass)
		{
			//USkill* Skill = ConstructObject<USkill>(SkillClass);
			USkill* Skill = NewObject<USkill>(GetTransientPackage(),SkillClass);
			Skill->Info = InInfo;
			Skill->Executor = InExecutor;
			//SkillCache.Add(InInfo->ID, Skill);
			return Skill;
		}
	}
	
	UE_LOG(Skill_LOG, Warning, TEXT("SkillClass is NULL"));
	return NULL;
}

void USkillSystem::ExecuteSkill(USkill* Skill)
{
	EExecuteStatus Status = Skill->Execute();
	if (Status == EExecuteStatus::Running)
	{
		SkillInstances.Add(Skill);
	}
}

void USkillSystem::ExecuteSkillWithTarget(USkill* Skill, AUnit* InTarget)
{
	EExecuteStatus Status = Skill->ExecuteWithTarget(InTarget);
	if (Status == EExecuteStatus::Running)
	{
		SkillInstances.Add(Skill);
	}
}

void USkillSystem::ExecuteSkillWithLocation(USkill* Skill, FVector InLocation)
{
	EExecuteStatus Status = Skill->ExecuteWithLocation(InLocation);
	if (Status == EExecuteStatus::Running)
	{
		SkillInstances.Add(Skill);
	}
}

void USkillSystem::ExecuteSkillWithDirection(USkill* Skill, FRotator InRotator)
{
	EExecuteStatus Status = Skill->ExecuteWithDirection(InRotator);
	if (Status == EExecuteStatus::Running)
	{
		SkillInstances.Add(Skill);
	}
}


void USkillSystem::Tick(float DeltaTime)
{
	for (auto Skill : SkillInstances)
	{
		EExecuteStatus Status = Skill->Tick(DeltaTime);
		if (Status == EExecuteStatus::Failed || Status == EExecuteStatus::Succeed)
		{
			SkillInstances.Remove(Skill);
		}
	}
}