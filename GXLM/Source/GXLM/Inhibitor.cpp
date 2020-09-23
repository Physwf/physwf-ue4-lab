// Fill out your copyright notice in the Description page of Project Settings.

#include "GXLM.h"
#include "Minion.h"
#include "Inhibitor.h"

DEFINE_LOG_CATEGORY(Inhibitor_LOG);

// Sets default values
AInhibitor::AInhibitor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<AMinion> SpiderClass(TEXT("/Game/BluePrints/Character/Minions/Bear"));
	if (SpiderClass.Class)
	{
		MinionClass = SpiderClass.Class;
		UE_LOG(Inhibitor_LOG, Warning, TEXT("SpiderClass is :%d"), SpiderClass.Class == NULL);
	}
}

// Called when the game starts or when spawned
void AInhibitor::BeginPlay()
{
	FVector SelfLocation = GetActorLocation();
	FVector CenterLocation(0.f, 0.f, 0.f);

	FVector MidDirectoin = CenterLocation - SelfLocation;
	MidDirectoin.Normalize();
	FVector DownDirection(MidDirectoin.X, 0.f, 0.f);
	DownDirection.Normalize();
	FVector UpDirection(0.f, MidDirectoin.Y, 0.f);
	UpDirection.Normalize();

	//SpawnDirections.Push(DownDirection.Rotation());
	SpawnDirections.Push(MidDirectoin.Rotation());
	//SpawnDirections.Push(UpDirection.Rotation());

	float Radius = 300.0f;
	FVector DownLocatioin = SelfLocation + DownDirection * Radius;
	FVector MidLocatioin = SelfLocation + MidDirectoin * Radius;
	FVector UpLocatioin = SelfLocation + UpDirection * Radius;

	//SpawnLocations.Push(DownLocatioin);
	SpawnLocations.Push(MidLocatioin);
	//SpawnLocations.Push(UpLocatioin);

	UE_LOG(Inhibitor_LOG, Warning, TEXT("SelfLocation:%s"), *SelfLocation.ToString());
	UE_LOG(Inhibitor_LOG, Warning, TEXT("DownLocatioin:%s"), *DownLocatioin.ToString());

	Super::BeginPlay();
	UE_LOG(Inhibitor_LOG, Warning, TEXT("BeginPlay"));
	if (Role == ROLE_Authority)
		GetWorld()->GetTimerManager().SetTimer(SpawnMinionTimer, this, &AInhibitor::SpawnMinion, 1.5f, false, 2.f);
}

void AInhibitor::EndPlay(EEndPlayReason::Type InReason)
{
	Super::EndPlay(InReason);
	if (Role == ROLE_Authority)
		GetWorld()->GetTimerManager().ClearTimer(SpawnMinionTimer);
}

// Called every frame
void AInhibitor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AInhibitor::SpawnMinion()
{
	//static UEnum* AliancePtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAliance"), true);
	for (int i = 0; i < SpawnLocations.Num(); ++i)
	{
		AMinion* Minion = (AMinion*)GetWorld()->SpawnActor<AMinion>(MinionClass, SpawnLocations[i], SpawnDirections[i]);
		if (Minion != NULL)
		{
			Minion->Alliance = Alliance;
			Minion->Type = EUnitType::Minion;
			UE_LOG(Inhibitor_LOG, Warning, TEXT("this->EnemyTowers.Num() is %d"), EnemyTowers.Num());
			Minion->EnemyTowers = &EnemyTowers;
		}
		
	}
}