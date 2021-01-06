// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GUI/SSPMenu.h"
#include "Shapr3DGameModeBase.generated.h"

class SCanvas;
/**
 * 
 */
UCLASS()
class SHAPR3D_API AShapr3DGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
private:
	TSharedPtr<SSPMenu> Menu;
	TSharedPtr<SCanvas> Canvas;
};
