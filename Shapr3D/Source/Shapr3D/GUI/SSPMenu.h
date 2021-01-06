// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "MySlateWidgetStyle.h"
/**
 * 
 */
class SSPMenuItem : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSPMenuItem):
		_IconBrush(FShapr3DStyle::Get().GetBrush("DefaultMenuItemIcon")),
		_IconText(FText::FromString(TEXT("DefaultIcon")))
	{}

	SLATE_ARGUMENT(const FSlateBrush*, IconBrush)
	SLATE_ARGUMENT(FText, IconText)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};

class SSPMenu : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSPMenu)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
};
