// Fill out your copyright notice in the Description page of Project Settings.

#include "GXLM.h"
#include "SummonerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Summoner.h"
#include "UIManager.h"
#include "UnrealNetWork.h"

ASummonerController::ASummonerController()
{
	bShowMouseCursor = true;
	bReplicates = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	static ConstructorHelpers::FClassFinder<AActor> TargetArrowClass(TEXT("/Game/BluePrints/Target"));

	UE_LOG(Summoner_LOG, Warning, TEXT("TargetArrowClass: %d"), TargetArrowClass.Class != NULL);
	if (TargetArrowClass.Class != NULL)
	{
		TargetArrow = TargetArrowClass.Class;
	}
	TargetArrowInstance = NULL;

    static ConstructorHelpers::FClassFinder<AHero> TrollClass(TEXT("/Game/BluePrints/Character/Heros/Troll"));
    if (TrollClass.Class != NULL)
    {
        MyHeroClass = TrollClass.Class;
    }
    static ConstructorHelpers::FClassFinder<AAIController> HeroControllerFinder(TEXT("/Game/BluePrints/AI/Hero/AC_Hero"));
    if (HeroControllerFinder.Class != NULL)
    {
       MyHeroControllerClass = HeroControllerFinder.Class;
    }
	
}

void ASummonerController::BeginPlay()
{
	//HealthBarManager::Owner = this;
	//UIManager::GetHealthBarMgr()->BeginPlay();
	AUnit::SkillSystem = NewObject<USkillSystem>(this);
	//AUnit::SkillSystem->AddToRoot();
    
    AltarLocation = FVector(0.f, 0.f, 250.f);
    //GetWorld()->GetTimerManager().SetTimer(SummonTimer, this, &ASummoner::Summon, 1.5f, false, 6.0f);
	if (Role == ROLE_Authority) 
		Summon();
	//LockViewToMyHero();
}

void ASummonerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}

	//SetActorLocation(GetControlledPawn()->GetActorLocation());
}

void ASummonerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Action", IE_Pressed, this, &ASummonerController::OnRightMousePressed);
	InputComponent->BindAction("Action", IE_Released, this, &ASummonerController::OnRightMouseReleased);
}

void ASummonerController::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		ServerSetNewMoveDestination(Hit.ImpactPoint);
        AActor* HitActor = Hit.GetActor();
        if(HitActor)
        {
            AUnit* Unit = Cast<AUnit>(HitActor);
			ServerSetAttackTarget(Unit);
            UE_LOG(Summoner_LOG, Warning, TEXT("Hit Actor is:%s"),*HitActor->GetName());
        }
	}
    else
    {
        UE_LOG(Summoner_LOG, Warning, TEXT("Hit.bBlockingHit is false"));
    }
}

bool ASummonerController::ServerSetNewMoveDestination_Validate(const FVector DestLocation)
{
	return true;
}

void ASummonerController::ServerSetNewMoveDestination_Implementation(const FVector DestLocation)
{
	
	ClientSetNewMoveDestination(DestLocation);
	//MyHeroInstance->MoveTo(DestLocation);
	
    MyHeroInstance->SetMoveTargetLocation(DestLocation);
}


void ASummonerController::ServerSetAttackTarget_Implementation(AUnit *InAttackTarget)
{
    GetMyHero()->SetAttackTarget(InAttackTarget);
}

bool ASummonerController::ServerSetAttackTarget_Validate(AUnit *InAttackTarget)
{
	return true;
}

void ASummonerController::SetFollowTarget(AUnit *InFollowUnit)
{
}

void ASummonerController::OnRightMousePressed()
{
	bMoveToMouseCursor = true;
}

void ASummonerController::OnRightMouseReleased()
{
	bMoveToMouseCursor = false;
}

void ASummonerController::Summon()
{
    MyHeroInstance = (AHero*)GetWorld()->SpawnActor(MyHeroClass, &AltarLocation);
    MyHeroController = (AAIController*)GetWorld()->SpawnActor(MyHeroControllerClass);
    MyHeroController->Possess(MyHeroInstance);
    if (MyHeroInstance)
    {
        MyHeroInstance->HomeLocation = AltarLocation;
        MyHeroInstance->MoveToLocation = AltarLocation;
		MyHeroInstance->Type = EUnitType::Hero;
    }
    if(Role == ROLE_Authority)
        LockViewToMyHero();
}

void ASummonerController::LockViewToMyHero()
{
    //ClientSetViewTarget(MyHeroInstance);
	UE_LOG(Summoner_LOG, Warning, TEXT("LockViewToMyHero"));
	ClientSetViewTarget(MyHeroInstance);
	GetWorld()->GetTimerManager().ClearTimer(SummonTimer);
}


void ASummonerController::ClientSetNewMoveDestination_Implementation(const FVector DestLocation)
{
	if (TargetArrowInstance == NULL)
	{
		TargetArrowInstance = GetWorld()->SpawnActor(TargetArrow, &DestLocation);
		UE_LOG(Summoner_LOG, Warning, TEXT("Create Target Arrow"));
	}
	else
	{
		TargetArrowInstance->SetActorLocation(DestLocation);
	}
}


void ASummonerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASummonerController, MyHeroInstance);
    DOREPLIFETIME(ASummonerController, MyHeroController);
}

void ASummonerController::OnRep_MyHeroInstance()
{
	if (MyHeroInstance == NULL)
	{
		UE_LOG(Summoner_LOG, Warning, TEXT("OnRep_MyHeroInstance: MyHeroInstance is NULL"));

	}
	else
	{
		UE_LOG(Summoner_LOG, Warning, TEXT("OnRep_MyHeroInstance"));
	}
	//ClientSetViewTarget(MyHeroInstance);
	//SetViewTarget(MyHeroInstance);
	GetWorld()->GetTimerManager().SetTimer(SummonTimer, this, &ASummonerController::LockViewToMyHero, 0.1f, false, 0.50f);
}