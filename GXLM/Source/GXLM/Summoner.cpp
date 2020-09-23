// Fill out your copyright notice in the Description page of Project Settings.

#include "GXLM.h"
#include "Summoner.h"
#include "SummonerController.h"

DEFINE_LOG_CATEGORY(Summoner_LOG);

// Sets default values
ASummoner::ASummoner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachTo(RootComponent);
	SpringArm->bAbsoluteRotation = true;
	SpringArm->TargetArmLength = 1000.f;
	SpringArm->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	SpringArm->bDoCollisionTest = false;

	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->AttachTo(SpringArm, USpringArmComponent::SocketName);
	TopDownCamera->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void ASummoner::BeginPlay()
{
	Super::BeginPlay();

	
	//SetActorLocation(FVector(0.f,0.f,0.f));

}

// Called every frame
void ASummoner::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
	//SetActorLocation(MyHeroInstance->GetActorLocation());
}

