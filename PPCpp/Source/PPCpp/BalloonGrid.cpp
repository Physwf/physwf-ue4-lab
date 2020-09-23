// Fill out your copyright notice in the Description page of Project Settings.

#include "PPCpp.h"
#include "BalloonGrid.h"


// Sets default values
ABalloonGrid::ABalloonGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABalloonGrid::BeginPlay()
{
	CreateGrid();
	MaxBalloonX = GridSizeX;
	Super::BeginPlay();
}


// Called every frame
void ABalloonGrid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABalloonGrid::CreateGrid()
{
	for (int32 y = 0; y < GridSizeY; ++y)
	{
		for (int32 x = 0; x < GridSizeX; ++x)
		{
			SP_Grid G = std::make_shared<Grid>();
			UE_LOG(YLog, Warning, TEXT("CreateGrid"));
			G->X = x;
			G->Y = y;
			Grids.Add(G);
		}
	}
}


void ABalloonGrid::FillBalloon(int32 InGridX, int32 InGridY, ABalloon* InBalloon)
{
	//UE_LOG(YLog, Warning, TEXT("FillBalloon"));
	SP_Grid G = Grids[InGridY*GridSizeX + InGridX];
	InBalloon->GridSpaceX = GridSpaceX;
	InBalloon->GridSpaceY = GridSpaceY;
	float LocX = (InGridX - GridSizeX / 2) * GridSpaceX;
	float LocY = (InGridY - GridSizeY / 2) * GridSpaceY;
	InBalloon->GridX = InGridX;
	InBalloon->GridY = InGridY;
	InBalloon->GridSizeX = GridSizeX;
	InBalloon->GridSizeY = GridSizeY;
	FVector Location(LocX, LocY, 0.0f);
	InBalloon->SetActorLocation(Location,false);
	G->Object = InBalloon;
}

void ABalloonGrid::TryPop(int32 InGridX, int32 InGridY)
{
	//UE_LOG(YLog, Warning, TEXT("TryPop start, X:%d,Y:%d"), InGridX, InGridY);
	int32 GridIndex = InGridY * GridSizeY + InGridX;
	SP_Grid G = Grids[GridIndex];
	if (!G->Object) return;
	EColorType Color = G->Object->Color;
	SearchResult.Add(G);
	G->Dirty = true;
	CrossSearch(InGridX, InGridY, Color);
	//UE_LOG(YLog, Warning, TEXT("TryPop finish %d"), SearchResult.Num());
	if (SearchResult.Num() < 2)
	{
		ClearGrid();
		SearchResult.Empty();
		return;
	}
	for (auto G : SearchResult)
	{
		PopCandidates.Add(G->Object);
	}
}

void ABalloonGrid::CrossSearch(int32 InGridX, int32 InGridY, EColorType Color)
{
	CrossSearchX(InGridX, InGridY, Color);
	//UE_LOG(YLog, Warning, TEXT("------------------"));
	CrossSearchY(InGridX, InGridY, Color);
}

void ABalloonGrid::CrossSearchX(int32 InGridX, int32 InGridY, EColorType Color)
{
	//UE_LOG(YLog, Warning, TEXT("CrossSearchX, X:%d,Y:%d"), InGridX, InGridY);
	for (int32 x = InGridX+1; x < GridSizeX; ++x)
	{
		int32 GridIndex = InGridY * GridSizeX + x;
		SP_Grid G = Grids[GridIndex];
		if (!G->Object) break;
		if (G->Object->Color != Color) break;
		if (!G->Dirty)
		{
			//UE_LOG(YLog, Warning, TEXT("CrossSearchX find success, X:%d,Y:%d"), x, InGridY);
			SearchResult.Add(G);
			G->Dirty = true;
			CrossSearchY(x, InGridY, Color);
		}
	}
	for (int32 x = InGridX-1; x > -1; --x)
	{
		//UE_LOG(YLog, Warning, TEXT("CrossSearchX finding, X:%d,Y:%d"), x, InGridY);
		int32 GridIndex = InGridY * GridSizeX + x;
		SP_Grid G = Grids[GridIndex];
		if (!G->Object)
		{
			//UE_LOG(YLog, Warning, TEXT("CrossSearchX finding, Object == NULL"));
			break;
		}
		if (G->Object->Color != Color)
		{
			//UE_LOG(YLog, Warning, TEXT("CrossSearchX finding, Color mismatch"));
			break;
		}
		if (!G->Dirty)
		{
			//UE_LOG(YLog, Warning, TEXT("CrossSearchX find success, X:%d,Y:%d"), x, InGridY);
			SearchResult.Add(G);
			G->Dirty = true;
			CrossSearchY(x, InGridY, Color);
		}
	}
}

void ABalloonGrid::CrossSearchY(int32 InGridX, int32 InGridY, EColorType Color)
{
	//UE_LOG(YLog, Warning, TEXT("CrossSearchY, X:%d,Y:%d"), InGridX, InGridY);
	for (int32 y = InGridY+1; y < GridSizeY; ++y)
	{
		int32 GridIndex = y * GridSizeX + InGridX;
		SP_Grid G = Grids[GridIndex];
		if (!G->Object) break;
		if (G->Object->Color != Color) break;
		if (!G->Dirty)
		{
			//UE_LOG(YLog, Warning, TEXT("CrossSearchY find success, X:%d,Y:%d"), InGridX, y);
			SearchResult.Add(G);
			G->Dirty = true;
			CrossSearchX(InGridX, y, Color);
		}
	}
	for (int32 y = InGridY-1; y > -1; --y)
	{
		int32 GridIndex = y * GridSizeX + InGridX;
		SP_Grid G = Grids[GridIndex];
		if (!G->Object) break;
		if (G->Object->Color != Color) break;
		if (!G->Dirty)
		{
			//UE_LOG(YLog, Warning, TEXT("CrossSearchY find success, X:%d,Y:%d"), InGridX, y);
			SearchResult.Add(G);
			G->Dirty = true;
			CrossSearchX(InGridX, y, Color);
		}
	}
}

void ABalloonGrid::ClearGrid()
{
	for (int32 y = 0; y < GridSizeY; ++y)
	{
		for (int32 x = 0; x < GridSizeX; ++x)
		{
			Grids[y*GridSizeX + x]->Dirty = false;
		}
	}
	
}

void ABalloonGrid::Pop()
{
	for (auto G : SearchResult)
	{
		G->Object = NULL;
	}
	PopCandidates.Empty();
}

void ABalloonGrid::Float()
{
	SP_Grid NullGrid;
	TArray<SP_Grid> Highest;
	Highest.Init(NullGrid, GridSizeX);
	for (auto G : SearchResult)
	{
		if (Highest[G->X] == NullGrid || Highest[G->X]->Y > G->Y)
		{
			Highest[G->X] = G;
		}
	}
	ABalloon* SignalBalloon = NULL;
	int32 OffsetMax = 0;
	for (auto G : Highest)
	{
		int32 FloatOffset = 1;
		if (G == NullGrid) continue;
		//UE_LOG(YLog, Warning, TEXT("Float, X:%d,Y:%d"), G->X, G->Y);
		for (int32 y = G->Y+1; y < GridSizeY; ++y)
		{
			SP_Grid GTemp = Grids[y*GridSizeX + G->X];
			if (GTemp->Object != NULL)
			{
				int32 TargetGridY = GTemp->Y - FloatOffset;
				if (FloatOffset > OffsetMax)
				{
					OffsetMax = FloatOffset;
					SignalBalloon = GTemp->Object;
				}
				GTemp->Object->SetTargetGrid(G->X, TargetGridY);
				Grids[TargetGridY*GridSizeX + G->X]->Object = GTemp->Object;
				GTemp->Object = NULL;
			}
			else
			{
				++FloatOffset;
			}
		}
		UE_LOG(YLog, Warning, TEXT("FloatOffset:%d"), FloatOffset);
		if (FloatOffset == GridSizeY)
		{
			--MaxBalloonX;
			UE_LOG(YLog, Warning, TEXT("MaxBalloonX:%d"), MaxBalloonX);
		}
	}
	Join();
	if (SignalBalloon)
	{
		UE_LOG(YLog, Warning, TEXT("SignalBalloon MaxBalloonX:%d"), MaxBalloonX);
		SignalBalloon->bIsSignal = true;
		SignalBalloon->NewBalloonX = MaxBalloonX;
	}
	else
	{
		SignalBalloon->gBalloonX = MaxBalloonX;
	}
	SearchResult.Empty();
}

void ABalloonGrid::Join()
{
	int32 JoinOffset = 0;
	for (int32 x = 0; x < GridSizeX; ++x)
	{
		SP_Grid G = Grids[x];
		if (G->Object == NULL)
		{
			JoinOffset++;
			UE_LOG(YLog, Warning, TEXT("Join JoinOffset:%d"), JoinOffset);
		}
		else if (JoinOffset>0)
		{
			for (int32 y = 0; y < GridSizeY; ++y)
			{
				UE_LOG(YLog, Warning, TEXT("Joining:%d"), y);
				SP_Grid Gy = Grids[y*GridSizeX+x];
				if (Gy->Object != NULL)
				{
					Grids[y*GridSizeX + Gy->X - JoinOffset]->Object = Gy->Object;
					Gy->Object->SetTargetGrid(Gy->X - JoinOffset, Gy->Y);
					Gy->Object = NULL;
				}
			}
		}
	}
}