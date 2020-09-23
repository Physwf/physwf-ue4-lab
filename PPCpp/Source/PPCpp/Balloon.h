// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Balloon.generated.h"

UENUM(BlueprintType)
enum class EColorType : uint8
{
	Red UMETA(DisplayName = "Red"),
	Green UMETA(DisplayName = "Green"),
	Blue UMETA(DisplayName = "Blue")
};

UCLASS()
class PPCPP_API ABalloon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABalloon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SetTargetGrid(int32 InGridX, int32 InGridY);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 GridX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 GridY;
	int32 TargetGridX;
	int32 TargetGridY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EColorType Color;

	float GridSpaceX;
	float GridSpaceY;
	int32 GridSizeX;
	int32 GridSizeY;
	int32 OldBalloonX;
	int32 NewBalloonX;
	static int32 gBalloonX;
	bool bIsSignal;
};
