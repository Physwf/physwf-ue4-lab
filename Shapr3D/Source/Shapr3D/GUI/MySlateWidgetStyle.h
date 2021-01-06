// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "Styling/SlateStyle.h"

struct SLATECORE_API FSlateDynamicImageBrush;

class FShapr3DSlateStyle : public  FSlateStyleSet
{
public:
	FShapr3DSlateStyle(const FName& InStyleSetName);
};

class FShapr3DStyle 
{
public:
	static TSharedRef<class ISlateStyle> Create(const FName& InStyleSetName = "Shapr3DStyle");

	static const ISlateStyle& Get()
	{
		return *(Instance.Get());
	}
	static void ResetToDefault();

	static const TSharedPtr<FSlateDynamicImageBrush> GetDynamicImageBrush(FName BrushTemplate, FName TextureName, const ANSICHAR* Specifier = nullptr);
private:
	static void SetStyle(const TSharedRef< class ISlateStyle >& NewStyle);
private:

	/** Singleton instances of this style. */
	static TSharedPtr< class ISlateStyle > Instance;
};

