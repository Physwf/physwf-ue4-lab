// Fill out your copyright notice in the Description page of Project Settings.

#include "PPCpp.h"
#include "Balloon.h"


// Sets default values
ABalloon::ABalloon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABalloon::BeginPlay()
{
	Super::BeginPlay();
	TargetGridX = GridX;
	TargetGridY = GridY;
	OldBalloonX = gBalloonX = GridSizeX;
}

// Called every frame
void ABalloon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//UE_LOG(YLog, Warning, TEXT("ABalloon::Tick,TargetGridX:%d,TargetGridY:%d"), TargetGridX, TargetGridY);
	//UE_LOG(YLog, Warning, TEXT("ABalloon::Tick,GridX:%d,GridY:%d"), GridX, GridY);
	if (TargetGridY != GridY)
	{
		float dy = Velocity * DeltaTime;
		float TargetY = (TargetGridY - GridSizeY/2) * GridSpaceY;
		//UE_LOG(YLog, Warning, TEXT("ABalloon::Tick,GridX:%d,GridY:%d,TargetY:%f"), GridX, GridY, TargetY);
		
		FVector Location = GetActorLocation();
		if (abs(Location.Y - TargetY) < dy)
		{
			Location.Y = TargetY;
			GridY = TargetGridY;
			if (bIsSignal)
			{
				gBalloonX = NewBalloonX;
			}
		}
		else
		{
			Location.Y -= dy;
			//UE_LOG(YLog, Warning, TEXT("ABalloon::Tick,dy:%f"), dy);
			//UE_LOG(YLog, Warning, TEXT("ABalloon::Tick,Location.Y:%f"), Location.Y);
		}
		SetActorLocation(Location, false);
	}
	if (OldBalloonX != gBalloonX)
	{
		float dx = Velocity * DeltaTime;
		float TargetX = (TargetGridX - gBalloonX / 2) * GridSpaceX;
		FVector Location = GetActorLocation();
		if (abs(Location.X - TargetX) <= dx)
		{
			Location.X = TargetX;
			OldBalloonX = gBalloonX;
			GridX = TargetGridX;
		}
		else
		{
			if (Location.X < TargetX) Location.X += dx;
			else Location.X -= dx;
			//UE_LOG(YLog, Warning, TEXT("ABalloon::Tick,dy:%f"), dy);
			//UE_LOG(YLog, Warning, TEXT("ABalloon::Tick,Location.Y:%f"), Location.Y);
		}
		SetActorLocation(Location, false);
	}
}

void ABalloon::SetTargetGrid(int32 InGridX, int32 InGridY)
{
	TargetGridX = InGridX;
	TargetGridY = InGridY;
}

int32 ABalloon::gBalloonX = 0;