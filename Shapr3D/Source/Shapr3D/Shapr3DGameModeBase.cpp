// Copyright Epic Games, Inc. All Rights Reserved.


#include "Shapr3DGameModeBase.h"
#include "Widgets/SWeakWidget.h"
#include "Widgets/SCanvas.h"
#include "GUI/MySlateWidgetStyle.h"

void AShapr3DGameModeBase::BeginPlay()
{
	FShapr3DStyle::ResetToDefault();

	Menu = SNew(SSPMenu);
	Canvas = SNew(SCanvas);
	Canvas->AddSlot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			Menu.ToSharedRef()
		];
	if (GEngine)
	{
		//GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(Menu));
		GEngine->GameViewport->AddViewportWidgetContent(Canvas.ToSharedRef());
	}
}
