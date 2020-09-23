// Fill out your copyright notice in the Description page of Project Settings.

#include "GXLM.h"
#include "Hero.h"
#include "HeroController.h"
#include "UIManager.h"
#include "UnrealNetwork.h"

DEFINE_LOG_CATEGORY(Hero_LOG);

AHero::AHero()
{
	//UClass* HeroControllerClass = FindObject<UClass>(ANY_PACKAGE, TEXT("AC_Hero"));
	//static ConstructorHelpers::FClassFinder<AAIController> HeroControllerFinder(TEXT("/Game/BluePrints/AI/Hero/AC_Hero"));
	//AIControllerClass = HeroControllerFinder.Class;
	UE_LOG(Hero_LOG, Warning, TEXT("AIControllerClass is %d"), AIControllerClass != NULL);
	//
	//AIControllerClass = AHeroController::StaticClass();

	TopDownCamera = NULL;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachTo(RootComponent);
	SpringArm->bAbsoluteRotation = true;
	SpringArm->TargetArmLength = 1000.f;
	SpringArm->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	SpringArm->bDoCollisionTest = false;

	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->AttachTo(SpringArm, USpringArmComponent::SocketName);
	TopDownCamera->bUsePawnControlRotation = false;

    AttackUnit = NULL;
    FollowUnit = NULL;
    
	//TopDownCamera->Deactive();
}

void AHero::ActiveCamera()
{
	//TopDownCamera->Active();
}

void AHero::MoveTo(const FVector DestLocation)
{
	MoveToLocation = DestLocation;
	float const Distance = FVector::Dist(DestLocation, GetActorLocation());
	//UE_LOG(Hero_LOG, Warning, TEXT("SetNewMoveDestination,Distance:%f"), Distance);
	//UE_LOG(Hero_LOG, Warning, TEXT("SetNewMoveDestination,NavSys:%d"), NavSystem != NULL);
	if (NavSystem && Distance > 120.f)
	{
		NavSystem->SimpleMoveToLocation(GetController(), DestLocation);
	}
}


void AHero::SetMoveTargetLocation(const FVector DestLocation)
{
	MoveToLocation = DestLocation;
	AttackUnit = NULL;
	FollowUnit = NULL;
}


void AHero::SetAttackTarget(AUnit* InAttackTarget)
{
	//MoveToTarget = DestLocation;
	AttackUnit = InAttackTarget;
	FollowUnit = NULL;
}

void AHero::SetFollowTarget(AUnit* InFollowTarget)
{
	//MoveToTarget = DestLocation;
	AttackUnit = NULL;
	FollowUnit = InFollowTarget;
}

void AHero::BeginPlay()
{
	Super::BeginPlay();

	NavSystem = GetWorld()->GetNavigationSystem();

	//pHealthBarElement = HealthBarElement::Create(0.02,0.2,0x00FF00,this);
	//pHealthBarElement->OnHealthChange(0, 50, 100);
	//HeathBar->AddElement(pHealthBarElement->Material, NULL, true, (float)pHealthBarElement->BaseSizeX, (float)pHealthBarElement->BaseSizeY, NULL);
	//UIManager::GetHealthBarMgr()->CreateHealthBar(GetName(), HealthBarType::OurHero);
	//UIManager::GetHealthBarMgr()->ShowHealthBar(GetName());

}

void AHero::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
	//UE_LOG(Hero_LOG, Warning, TEXT("Tick,V:%f"), GetVelocity().Size());
	//UE_LOG(Hero_LOG, Warning, TEXT("Tick,IsAttacking:%d"), UnitProperty->IsAttacking);
	if (GetVelocity().GetAbsMax() <= 0.0f)
	{
		float const Distance = (MoveToLocation - GetActorLocation()).Size2D();
	}
	else
	{

	}

	//FVector ActorLocation = GetActorLocation();
	//ActorLocation.Z += 200.f;
	//UIManager::GetHealthBarMgr()->UpdateHealthBar(GetName(), ActorLocation);
	for (auto SI : Skills)
	{
		SI->doCD(DeltaSecond);
	}
}


USkillInfo* AHero::SelectSkillByIndex(int32 InIndex)
{
    check(InIndex < Skills.Num());
    SelectedSkill = Skills[InIndex];
    return SelectedSkill;
}

void AHero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//DOREPLIFETIME(AHero, MoveToLocation);
}