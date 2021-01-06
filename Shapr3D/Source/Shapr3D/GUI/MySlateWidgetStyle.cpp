// Fill out your copyright notice in the Description page of Project Settings.


#include "MySlateWidgetStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Brushes/SlateDynamicImageBrush.h"

FShapr3DSlateStyle::FShapr3DSlateStyle(const FName& InStyleSetName)
	: FSlateStyleSet(InStyleSetName)
{

}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

TSharedRef<class ISlateStyle> FShapr3DStyle::Create(const FName& InStyleSetName /*= "Shapr3DStyle"*/)
{
	TSharedRef<FShapr3DSlateStyle> Style = MakeShareable(new FShapr3DSlateStyle(InStyleSetName));
	Style->SetContentRoot(FPaths::ProjectContentDir() / TEXT("Slate"));

	const FVector2D Icon64x64(64.0f, 64.0f);

	Style->Set("DefaultMenuItemIcon", new IMAGE_BRUSH("Icons/DefaultMenuItemIcon", Icon64x64));
	Style->Set("Create", new IMAGE_BRUSH("Icons/Create", Icon64x64));
	Style->Set("Edit", new IMAGE_BRUSH("Icons/Edit", Icon64x64));
	Style->Set("Sculpting", new IMAGE_BRUSH("Icons/Sculpting", Icon64x64));

	return Style;
}

void FShapr3DStyle::ResetToDefault()
{
	SetStyle(FShapr3DStyle::Create());
}

const TSharedPtr<FSlateDynamicImageBrush> FShapr3DStyle::GetDynamicImageBrush(FName BrushTemplate, FName TextureName, const ANSICHAR* Specifier /*= nullptr*/)
{
	return Instance->GetDynamicImageBrush(BrushTemplate, TextureName, Specifier);
}

void FShapr3DStyle::SetStyle(const TSharedRef< class ISlateStyle >& NewStyle)
{
	if (Instance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*Instance.Get());
	}

	Instance = NewStyle;

	if (Instance.IsValid())
	{
		FSlateStyleRegistry::RegisterSlateStyle(*Instance.Get());
	}
	else
	{
		ResetToDefault();
	}
}

TSharedPtr< class ISlateStyle > FShapr3DStyle::Instance = NULL;
