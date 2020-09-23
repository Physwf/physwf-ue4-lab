// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Blueprint/UserWidget.h"
#include "WidgetLayoutLibrary.h"
class USlateBrushAsset;
#include "ProgressBar.h"
#include "CanvasPanel.h"

DECLARE_LOG_CATEGORY_EXTERN(UIManager_LOG, Log, All);

enum HealthBarType
{
	OurHero,
	TheirHero,
	OurTower,
	TheirTower
};

class HealthBarManager
{
public:
	friend class UIManager;

	~HealthBarManager();
	
	void BeginPlay();
	bool CreateHealthBar(FString Name, HealthBarType Type);
	void UpdateHealthBar(FString Name, FVector &WorldPosition);
	void ShowHealthBar(FString Name);
	void HideHealthBar(FString Name);

	static UClass* UMGHealthBarLayerClass;
	static UClass* UMGHeroHealthBarClass;
	static UClass* UMGTowerHealthBarClass;
	static APlayerController* Owner;

private:
	HealthBarManager();

	UUserWidget* HealthBarLayer;
	UCanvasPanel* Canvas;
	TMap<FString, UProgressBar*> HealthBarList;
};

/**
 * 
 */
class GXLM_API UIManager
{
public:
	UIManager();
	~UIManager();
	static HealthBarManager* GetHealthBarMgr();
private:
	static HealthBarManager* HealthBarMgr;
};
