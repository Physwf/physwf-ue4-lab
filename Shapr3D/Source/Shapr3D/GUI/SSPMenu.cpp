// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPMenu.h"
#include "SlateOptMacros.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "MySlateWidgetStyle.h"

#define LOCTEXT_NAMESPACE "Shapr3D"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSPMenuItem::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		// Populate the widget
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		[
			SNew(SImage).Image(InArgs._IconBrush)
		]
		+ SVerticalBox::Slot()
		[
			SNew(STextBlock).Text(InArgs._IconText)
		]
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSPMenu::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		// Populate the widget
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		[
			SNew(SSPMenuItem)
			.IconBrush(FShapr3DStyle::Get().GetBrush("Create"))
			.IconText(LOCTEXT("Icon_Create","Create"))
		]
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		+ SVerticalBox::Slot()
		[
			SNew(SSPMenuItem)
			.IconBrush(FShapr3DStyle::Get().GetBrush("Edit"))
			.IconText(LOCTEXT("Icon_Edit", "Edit"))
		]
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		+ SVerticalBox::Slot()
		[
			SNew(SSPMenuItem)
			.IconBrush(FShapr3DStyle::Get().GetBrush("Sculpting"))
			.IconText(LOCTEXT("Icon_Sculpting", "Sculpting"))
		]
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE