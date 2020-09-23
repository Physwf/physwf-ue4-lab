// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <memory>
#include "GameFramework/Actor.h"
#include "PPCpp/Balloon.h"
#include "BalloonGrid.generated.h"


struct Grid
{
	int32 X{ 0 };
	int32 Y{ 0 };
	ABalloon* Object{NULL};
	bool Dirty{ false };
};
typedef std::shared_ptr<Grid> SP_Grid;

UCLASS()
class PPCPP_API ABalloonGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABalloonGrid();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	void CreateGrid();
	UFUNCTION(BlueprintCallable,Category="Game")
	void FillBalloon(int32 InGridX, int32 InGridY, ABalloon* InBalloon);
	UFUNCTION(BlueprintCallable, Category = "Game")
	void TryPop(int32 InGridX, int32 InGridY);
	void CrossSearch(int32 InGridX, int32 InGridY, EColorType Color);
	inline void CrossSearchX(int32 InGridX, int32 InGridY, EColorType Color);
	inline void CrossSearchY(int32 InGridX, int32 InGridY, EColorType Color);
	UFUNCTION(BlueprintCallable, Category = "Game")
	void ClearGrid();
	UFUNCTION(BlueprintCallable, Category = "Game")
	void Pop();
	UFUNCTION(BlueprintCallable, Category = "Game")
	void Float();
	void Join();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 GridSizeX;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 GridSizeY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GridSpaceX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GridSpaceY;
	UPROPERTY(BlueprintReadOnly)
	TArray<ABalloon*> PopCandidates;
private:
	TArray<SP_Grid> SearchResult;
	TArray<SP_Grid> PopGrids;
	TArray<SP_Grid> Grids;
	int32 MaxBalloonX;
};
