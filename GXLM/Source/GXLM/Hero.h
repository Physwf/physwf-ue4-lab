// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Skill.h"
#include "Unit.h"
#include "Hero.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Hero_LOG, Log, All);
/**
 * 
 */
UCLASS()
class GXLM_API AHero : public AUnit
{
	GENERATED_BODY()

	
public:
	friend class ASummoner;

	AHero();

	void ActiveCamera();
	void MoveTo(const FVector DestLocation);
	void SetMoveTargetLocation(const FVector DestLocation);

	void SetAttackTarget(AUnit* InAttackTarget);
	void SetFollowTarget(AUnit* InFollowTarget);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Hero")
	FVector GetHomeLocation() const { return HomeLocation; }
    UFUNCTION(BlueprintCallable, Category="Hero")
    USkillInfo* GetSelectedSkill() const { return SelectedSkill; }
    UFUNCTION(BlueprintCallable, Category="Hero")
    USkillInfo* SelectSkillByIndex(int32 InIndex);
    
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Hero")
	FVector HomeLocation;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Hero")
	FVector MoveToLocation;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Hero")
	AUnit* AttackUnit;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Hero")
	AUnit* FollowUnit;
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Hero")
    AUnit* SkillTargetUnit;
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Hero")
    FVector SkillTargetLocation;
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Hero")
    FRotator SkillTargetDirection;
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Hero")
    TArray<USkillInfo*> Skills;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const;
private:
	class UCameraComponent* TopDownCamera;
	class USpringArmComponent* SpringArm;
	UNavigationSystem* NavSystem;
    USkillInfo* SelectedSkill;
};
