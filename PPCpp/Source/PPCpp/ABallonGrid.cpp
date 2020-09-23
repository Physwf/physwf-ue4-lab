// Fill out your copyright notice in the Description page of Project Settings.

#include "PPCpp.h"
#include "ABallonGrid.h"


// Sets default values
AABallonGrid::AABallonGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AABallonGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABallonGrid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

