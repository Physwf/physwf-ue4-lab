// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "Blueprint/UserWidget.h"
#include "Hero.h"
#include "SummonerController.generated.h"
/*

*/
/**
 * 
 */
UCLASS()
class GXLM_API ASummonerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASummonerController();

	
protected:

	uint32 bMoveToMouseCursor : 1;

	//Begin PlayerController Interface
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	//End PlayerController Interface
	void MoveToMouseCursor();
	//bool ServerMoveToMouseCursor_Validate();


	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetNewMoveDestination(const FVector DestLocation);
	void ServerSetNewMoveDestination_Implementation(const FVector DestLocation);
	bool ServerSetNewMoveDestination_Validate(const FVector DestLocation);
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetAttackTarget(AUnit* InAttackTarget);
	void ServerSetAttackTarget_Implementation(AUnit* InAttackTarget);
	bool ServerSetAttackTarget_Invalidate(AUnit* InAttackTarget);

    void SetFollowTarget(AUnit* InFollowUnit);
    
	void OnRightMousePressed();
	void OnRightMouseReleased();
    
    UFUNCTION(BlueprintCallable, Category = "Summoner")
    AHero* GetMyHero() const { return MyHeroInstance; }

    void Summon();

	UFUNCTION(Client,Reliable)
	void ClientSetNewMoveDestination(const FVector DestLocation);
	void ClientSetNewMoveDestination_Implementation(const FVector DestLocation);
	//bool ClientSetNewMoveDestination_Validate(const FVector DestLocation);
	//UFUNCTION(Client, Reliable)
	void LockViewToMyHero();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const;
	UFUNCTION()
	void OnRep_MyHeroInstance();
private:
	UClass* TargetArrow;
	AActor* TargetArrowInstance;
    UClass* MyHeroClass;
    UClass* MyHeroControllerClass;
	UPROPERTY(ReplicatedUsing = OnRep_MyHeroInstance)
    AHero* MyHeroInstance;
    UPROPERTY(replicated)
    AAIController* MyHeroController;
    FVector AltarLocation;
	FTimerHandle SummonTimer;
};
