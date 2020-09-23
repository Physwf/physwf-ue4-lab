// Fill out your copyright notice in the Description page of Project Settings.

#include "GXLM.h"
#include "Skill.h"
#include "UnrealNetwork.h"

DEFINE_LOG_CATEGORY(Unit_LOG);

HealthBarElement::HealthBarElement()
{

}

HealthBarElement::~HealthBarElement()
{

}

UMaterial* HealthBarElement::HealthMaterial = NULL;

HealthBarElement* HealthBarElement::Create(uint32 InBaseSizeX, uint32 InBaseSizeY, uint32 InHealthColor, UObject* InOwner)
{
	HealthBarElement* Result = new HealthBarElement();
	Result->BaseSizeX = (float)InBaseSizeX;
	Result->BaseSizeY = (float)InBaseSizeY;
	Result->TextureSizeX = InBaseSizeX;
	Result->TextureSizeY = InBaseSizeY;
	Result->HealthColor = InHealthColor;
	Result->Material = UMaterialInstanceDynamic::Create(HealthMaterial, InOwner);
	Result->HeathTexture = UTexture2D::CreateTransient(Result->TextureSizeX, Result->TextureSizeY);
	//Result->HeathTexture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	Result->HeathTexture->CompressionSettings = TextureCompressionSettings::TC_EditorIcon;
	Result->HeathTexture->SRGB = 0;
	Result->HeathTexture->AddToRoot();
	Result->HeathTexture->UpdateResource();
	Result->Material->SetTextureParameterValue(FName("HealthTextureParam"), Result->HeathTexture);
	Result->UpdateRegion = new FUpdateTextureRegion2D(0, 0, 0, 0, Result->TextureSizeX, Result->TextureSizeY);
	Result->PixelBuffer = new uint32[InBaseSizeX*InBaseSizeY];
	return Result;
}

void HealthBarElement::OnHealthChange(int32 amount, int32 Health, int32 MaxHealth)
{
	uint32 PixelCount = TextureSizeX * TextureSizeY;
	uint32 BloodSize = TextureSizeX*((float)Health / MaxHealth);
	UE_LOG(Unit_LOG, Log, TEXT("PixelCount%d,BloodSize:%d"), PixelCount, BloodSize);
	uint8* Pixels = (uint8*)PixelBuffer;
	for (uint32 i = 0; i < PixelCount/2; ++i)
	{
		uint32 iB = i * 4 + 0;
		uint32 iG = i * 4 + 1;
		uint32 iR = i * 4 + 2;
		uint32 iA = i * 4 + 3;

		uint32 iX = i % TextureSizeX;
		uint32 iY = i / TextureSizeX;
		PixelBuffer[i] = HealthColor;
		/*
		if (iX < BloodSize)
		{
			//PixelBuffer[i] = HealthColor;
			Pixels[iB] = 0;
			Pixels[iG] = 0;
			Pixels[iR] = 255;
			Pixels[iA] = 255;
			UE_LOG(Unit_LOG, Log, TEXT("iX:%d,i:%d,"), iX, i);
		}
		else
		{
			Pixels[iB] = 0;
			Pixels[iG] = 0;
			Pixels[iR] = 0;
			Pixels[iA] = 255;
			//PixelBuffer[i] = 0;
		}
	*/
	}
	/*
	for (uint32 i = 0; i < PixelCount; ++i)
	{
		//uint32 iB = i * 4 + 0;
		//uint32 iG = i * 4 + 1;
		//uint32 iR = i * 4 + 2;
		//uint32 iA = i * 4 + 3;

		uint32 iX = i / TextureSizeY;
		PixelBuffer[i] = 0;
		if (iX > BloodSize)
		{
			PixelBuffer[i] = HealthColor;
		}
	}*/

	UpdateTextureRegions(HeathTexture, 0, 1, UpdateRegion, TextureSizeX * 4, (uint32)4, (uint8*)PixelBuffer, false);
}

void HealthBarElement::UpdateTextureRegions(UTexture2D* Texture, int32 MipIndex, uint32 NumRegions, FUpdateTextureRegion2D* Regions, uint32 SrcPitch, uint32 SrcBpp, uint8* SrcData, bool bFreeData)
{
	if (Texture && Texture->Resource)
	{
		struct FUpdateTextureRegionsData
		{
				FTexture2DResource* Texture2DResource;
				int32 MipIndex;
				uint32 NumRegions;
				FUpdateTextureRegion2D* Regions;
				uint32 SrcPitch;
				uint32 SrcBpp;
				uint8* SrcData;
		};
			FUpdateTextureRegionsData* RegionData = new FUpdateTextureRegionsData;

			RegionData->Texture2DResource = (FTexture2DResource*)Texture->Resource;
			RegionData->MipIndex = MipIndex;
			RegionData->NumRegions = NumRegions;
			RegionData->Regions = Regions;
			RegionData->SrcPitch = SrcPitch;
			RegionData->SrcBpp = SrcBpp;
			RegionData->SrcData = SrcData;

			ENQUEUE_UNIQUE_RENDER_COMMAND_TWOPARAMETER(
			UpdateTextureRegionsData,
			FUpdateTextureRegionsData*, RegionData, RegionData,
			bool, bFreeData, bFreeData,
		{
				for (uint32 RegionIndex = 0; RegionIndex < RegionData->NumRegions; ++RegionIndex)
				{
						int32 CurrentFirstMip = RegionData->Texture2DResource->GetCurrentFirstMip();
						if (RegionData->MipIndex >= CurrentFirstMip)
						{
								RHIUpdateTexture2D(
								RegionData->Texture2DResource->GetTexture2DRHI(),
								RegionData->MipIndex - CurrentFirstMip,
								RegionData->Regions[RegionIndex],
								RegionData->SrcPitch,
								RegionData->SrcData
								+ RegionData->Regions[RegionIndex].SrcY * RegionData->SrcPitch
								+ RegionData->Regions[RegionIndex].SrcX * RegionData->SrcBpp
								);
						}
				}

				if (bFreeData)
				{
						FMemory::Free(RegionData->Regions);
						FMemory::Free(RegionData->SrcData);
				}
				delete RegionData;
		});
	}

}

void HealthBarElement::Tick(float DeltaTime)
{

}
// Sets default values
AUnit::AUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//static ConstructorHelpers::FObjectFinder<UMaterial> HealthMaterialFinder(TEXT("/Game/Materials/HealthBar"));
	//HealthBarElement::HealthMaterial = HealthMaterialFinder.Object;
	//UE_LOG(Unit_LOG, Log, TEXT("HealthMaterialFinder.Object is %d"), HealthMaterialFinder.Object!=NULL);

	//HeathBar = CreateDefaultSubobject<UMaterialBillboardComponent>(TEXT("HealthBar"));
	//HeathBar->RelativeLocation = FVector(0.f, 0.f, 256.f);
	//HeathBar->AttachTo(RootComponent);
	//HeathBar->AddElement();

}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	AddHealth(MaxHealth);
}

// Called every frame
void AUnit::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
}

// Called to bind functionality to input
void AUnit::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AUnit::AddHealth_Implementation(int32 amount)
{
	Health += amount;
	Health = FMath::Max(Health, MaxHealth);
	OnHealthAdd.Broadcast(amount, Health, MaxHealth);
}

void AUnit::LoseHealth_Implementation(int32 amount)
{
	Health -= amount;
	Health = FMath::Max(Health, 0);
	UE_LOG(Unit_LOG, Warning, TEXT("Unit %s lose health amount %d, current health is:%d"), *GetName(), amount, Health);
	OnHealthLose.Broadcast(amount, Health, MaxHealth);
}

USkillSystem* AUnit::SkillSystem = NULL;

void AUnit::DischargeSkill(USkillInfo* InInfo)
{
	USkill* Skill = SkillSystem->SpawnSkill(InInfo, this);
	SkillSystem->ExecuteSkill(Skill);
}

void AUnit::DischargeSkillWithTarget(USkillInfo* InInfo, AUnit* InTarget)
{
	//UE_LOG(Unit_LOG, Warning, TEXT("DischargeSkill: %s WithTarget: %s") , *InInfo->Name,*InTarget->GetName());
	InInfo->CD = InInfo->CDTime;
	USkill* Skill = SkillSystem->SpawnSkill(InInfo, this);
	SkillSystem->ExecuteSkillWithTarget(Skill, InTarget);
}


void AUnit::DischargeSkillWithLocation(USkillInfo* InInfo, const FVector Location)
{

}

void AUnit::DischargeSkillWithDirection(USkillInfo* InInfo, const FVector Direction)
{

}

void AUnit::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AUnit, IsAttacking);
}