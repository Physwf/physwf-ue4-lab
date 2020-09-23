// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Hero.h"
#include "Blueprint/UserWidget.h"
#include "Summoner.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Summoner_LOG, Log, All);

UCLASS()
class GXLM_API ASummoner : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASummoner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;



private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	UClass* MyHeroClass;
	AHero* MyHeroInstance;
	FVector AltarLocation;
	FTimerHandle SummonTimer;
};
