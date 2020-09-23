// Fill out your copyright notice in the Description page of Project Settings.

#include "GXLM.h"
#include "UIManager.h"

DEFINE_LOG_CATEGORY(UIManager_LOG);

HealthBarManager::HealthBarManager()
{

}

HealthBarManager::~HealthBarManager()
{

}

void HealthBarManager::BeginPlay()
{
	UE_LOG(UIManager_LOG, Warning, TEXT("HealthBarManager BeginPlay"));
	check(UMGHealthBarLayerClass!=NULL);
	if (UMGHealthBarLayerClass)
	{
		check(HealthBarLayer != NULL);
		HealthBarLayer = CreateWidget<UUserWidget>(Owner, UMGHealthBarLayerClass);
		HealthBarLayer->AddToViewport();
		Canvas = (UCanvasPanel*)HealthBarLayer->GetRootWidget();
		check(Canvas != NULL);
	}
}

bool HealthBarManager::CreateHealthBar(FString Name, HealthBarType Type)
{
	UE_LOG(UIManager_LOG, Warning, TEXT("CreateHealthBar"));
	if (HealthBarList.Find(Name) != nullptr) return false;
	UClass* WidgetClass = NULL;
	FColor Color(0);
	switch (Type)
	{
	case HealthBarType::OurHero:
		WidgetClass = UMGHeroHealthBarClass;
		Color.G = 255;
		break;
	case HealthBarType::TheirHero:
		WidgetClass = UMGHeroHealthBarClass;
		Color.R = 255;
		break;
	case HealthBarType::OurTower:
		WidgetClass = UMGTowerHealthBarClass;
		Color.G = 255;
		break;
	case HealthBarType::TheirTower:
		WidgetClass = UMGTowerHealthBarClass;
		Color.R = 255;
		break;
	}
	check(WidgetClass != NULL);
	check(Owner != NULL);
	UProgressBar* PB = NewObject<UProgressBar>(Owner, UProgressBar::StaticClass());
	UE_LOG(UIManager_LOG, Warning, TEXT("UProgressBar is %d"), PB != NULL);
	check(PB != NULL);
	PB->FillColorAndOpacity = Color;
	PB->SetVisibility(ESlateVisibility::Hidden);
	Canvas->AddChild(PB);
	HealthBarList.Add(Name, PB);
	return true;
}

void HealthBarManager::UpdateHealthBar(FString Name, FVector &WorldPosition)
{
	FVector2D ScreenPosition;
	Owner->ProjectWorldLocationToScreen(WorldPosition, ScreenPosition);
	if (UProgressBar** pPB = HealthBarList.Find(Name))
	{
		(*pPB)->SetRenderTranslation(ScreenPosition);
		UE_LOG(UIManager_LOG, Warning, TEXT("UpdateHealthBar %s'ScreenPosition:%s"), *Name, *ScreenPosition.ToString());
	}
}

void HealthBarManager::ShowHealthBar(FString Name)
{
	if (UProgressBar** pPB = HealthBarList.Find(Name))
	{
		(*pPB)->SetVisibility(ESlateVisibility::Visible);
	}
}

void HealthBarManager::HideHealthBar(FString Name)
{
	if (UProgressBar** pPB = HealthBarList.Find(Name))
	{
		(*pPB)->SetVisibility(ESlateVisibility::Hidden);
	}
}

UClass* HealthBarManager::UMGHealthBarLayerClass = NULL;
UClass* HealthBarManager::UMGHeroHealthBarClass = NULL;
UClass* HealthBarManager::UMGTowerHealthBarClass = NULL;
APlayerController* HealthBarManager::Owner = NULL;

UIManager::UIManager()
{

}

UIManager::~UIManager()
{
}

HealthBarManager* UIManager::HealthBarMgr = new HealthBarManager();

HealthBarManager* UIManager::GetHealthBarMgr()
{
	return HealthBarMgr;
}
