// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "UnitProperty.h"
#include "Unit.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthChangeDelegate, int32, Delta, int32, Health, int32, MaxHealth);
DECLARE_LOG_CATEGORY_EXTERN(Unit_LOG, Log, All);

class USkill;
class USkillInfo;
class USkillSystem;

UCLASS()
class GXLM_API AUnit : public ACharacter
{
	GENERATED_BODY()

public:
	friend class ASummonerController;
	// Sets default values for this character's properties
	AUnit();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Unit")
	virtual void AddHealth(int32 amount);
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Unit")
	virtual void LoseHealth(int32 amount);

	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual int32 GetHealth()const { return Health; }
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual bool IsDead() const{ return Health <= 0; }

	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual bool IsEnemy(AUnit* InUnit) const { return InUnit->Alliance != Alliance; }
	
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual void DischargeSkill(USkillInfo* InInfo);
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual void DischargeSkillWithTarget(USkillInfo* InInfo, AUnit* InTarget);
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual void DischargeSkillWithLocation(USkillInfo* InInfo, const FVector Location);
	UFUNCTION(BlueprintCallable, Category = "Unit")
	virtual void DischargeSkillWithDirection(USkillInfo* InInfo, const FVector Direction);
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit")
	int32 MaxHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit")
	float UnitSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit")
	EAliance Alliance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit")
	EUnitType Type;

	UPROPERTY(Replicated,BlueprintReadWrite, EditAnywhere, Category = "Unit")
	bool IsAttacking;

	UPROPERTY(BlueprintAssignable, EditAnywhere, Category = "Unit")
	FHealthChangeDelegate OnHealthAdd;
	UPROPERTY(BlueprintAssignable, EditAnywhere, Category = "Unit")
	FHealthChangeDelegate OnHealthLose;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	//UMaterialBillboardComponent* HeathBar;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & Props) const;
private:
	int32 Health;
	static USkillSystem* SkillSystem;
};

struct HealthBarElement
{
	UMaterialInstanceDynamic* Material;
	UCurveFloat* DistanceToOpacityCurve;
	bool bSizeIsInScreenSpace;
	float BaseSizeX;
	float BaseSizeY;
	UCurveFloat* DistanceToSizeCurve;

	uint32 HealthColor;
	static UMaterial* HealthMaterial;
	UTexture2D* HeathTexture;
	uint32* PixelBuffer;
	FUpdateTextureRegion2D* UpdateRegion;
	uint32 TextureSizeX;
	uint32 TextureSizeY;
private:
	HealthBarElement();
	HealthBarElement(const HealthBarElement&) = delete;
	//operator=(const HealthBarElement&) = delete;
public:
	~HealthBarElement();

	static HealthBarElement* Create(uint32 InBaseSizeX, uint32 InBaseSizeY, uint32 InHealthColor, UObject* InOwner);
	void OnHealthChange(int32 amount, int32 Health, int32 MaxHealth);
	void UpdateTextureRegions(UTexture2D* Texture, int32 MipIndex, uint32 NumRegions, FUpdateTextureRegion2D* Regions, uint32 SrcPitch, uint32 SrcBpp, uint8* SrcData, bool bFreeData);
	void Tick(float DeltaTime);
};