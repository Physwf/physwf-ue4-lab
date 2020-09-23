// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "UnitProperty.h"
#include "Unit.h"
#include "Skill.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Skill_LOG, Log, All);

UENUM(Blueprintable)
enum class ESkillType : uint8
{
	Buff UMETA(DisplayName = "Buff")

};

UENUM(Blueprintable)
enum class EExecuteStatus : uint8
{
	Running UMETA(DisplayName = "Running"),
	Succeed UMETA(DisplayName = "Succeed"),
	Failed UMETA(DisplayName = "Failed")
};

UCLASS(Blueprintable)
class USkillInfo : public UObject
{
	GENERATED_BODY()
public:
	friend class AUnit;

	UFUNCTION(BlueprintImplementableEvent, Category = "Verify")
	bool Verify(AUnit* Discharger);
	UFUNCTION(BlueprintCallable, Category = "Verify")
	bool IsCDing() { return CD > 0.f; }

	FORCEINLINE void doCD(float DeltaTime) { CD -= DeltaTime; }

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Basic")
	int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	ESkillType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	FString AnimName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
    float MinDischargeDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	float CDTime;
private:
	float CD;
};
/**
 * 
 */
UCLASS(Blueprintable)
class GXLM_API USkill : public UObject
{
	GENERATED_BODY()
	
public:
	friend class USkillSystem;

	USkill();

	UFUNCTION(BlueprintNativeEvent, Category = "Skill")
	EExecuteStatus Execute();
	UFUNCTION(BlueprintNativeEvent, Category = "Skill")
	EExecuteStatus ExecuteWithTarget(AUnit* InTarget);
	UFUNCTION(BlueprintNativeEvent, Category = "Skill")
	EExecuteStatus ExecuteWithLocation(FVector InLocation);
	UFUNCTION(BlueprintNativeEvent, Category = "Skill")
	EExecuteStatus ExecuteWithDirection(FRotator InRotator);
	UFUNCTION(BlueprintNativeEvent, Category = "Skill")
	EExecuteStatus Tick(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Utility")
	bool IsTargetInRange(AUnit* InTarget,float InRange);
	UFUNCTION(BlueprintCallable, Category = "Utility")
	bool IsTargetInFront(AUnit* InTarget, float Degree);

	UPROPERTY(BlueprintReadOnly, Category = "Skill")
	USkillInfo *Info;
	UPROPERTY(BlueprintReadOnly, Category = "Skill")
	AUnit* Executor;
};

UCLASS()
class GXLM_API USkillSystem : public UObject
{
	GENERATED_BODY()
public:
	friend class AUnit;

	USkillSystem();
	USkill* SpawnSkill(USkillInfo* InInfo, AUnit* InExecutor);
	void ExecuteSkill(USkill* Skill);
	void ExecuteSkillWithTarget(USkill* Skill, AUnit* InTarget);
	void ExecuteSkillWithLocation(USkill* Skill, FVector InLocation);
	void ExecuteSkillWithDirection(USkill* Skill, FRotator InRotator);
	void Tick(float DeltaTime);
private:
	TMap<int32, USkill*> SkillCache;
	TArray<USkill*> SkillInstances;
};