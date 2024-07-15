// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/CharacterComponents/BaseSpellComponent.h"

#include "VectorUtil.h"
#include "Core/Characters/GameCharacter.h"
#include "Core/HexMapSystem/HexCell.h"
#include "Kismet/BlueprintTypeConversions.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/DungeonPlayerController.h"

// Sets default values for this component's properties
UBaseSpellComponent::UBaseSpellComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseSpellComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SpellCaster = Cast<AGameCharacter>(GetOwner());
	
}


// Called every frame
void UBaseSpellComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseSpellComponent::OnSelectSpell()
{
	ADungeonPlayerController* PlayerController = Cast<ADungeonPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->SetTurnState(ETurnState::CastingSpell);
	PlayerController->SetSelectedSpell(this);
}

bool UBaseSpellComponent::CheckHit(AGameCharacter* SpellTarget)
{
	int TotalPrecision = Precision + SpellCaster->GetPrecision() - SpellTarget->DodgeChances();
	TotalPrecision = UE::Geometry::VectorUtil::Clamp(TotalPrecision, 5, 95);
	return FMath::RandRange(1, 100) <= TotalPrecision;
}

bool UBaseSpellComponent::CheckRange(AGameCharacter* SpellTarget)
{
	int Distance = SpellCaster->GetHexLocation()->Distance(SpellTarget->GetHexLocation());
	return (RangeMin <= Distance && Distance  <= RangeMax);
}

int UBaseSpellComponent::GenerateDamage()
{
	return (FMath::RandRange(SpellCaster->GetAttackLesser(), SpellCaster->GetAttackGreater()) * DamageRatio / 100);
}

bool UBaseSpellComponent::CheckCritic()
{
	int TotalCriticalChances = SpellCaster->GetCriticalChances() + CriticalChances;
	return (FMath::RandRange(1, 100) <= TotalCriticalChances);
	
}

void UBaseSpellComponent::CastSpell_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Warning: CastSpell Must be Overriden"));	
}

bool UBaseSpellComponent::IsSpellSelected() const
{
	return bSpellSelected;
}

void UBaseSpellComponent::SetSpellSelected(bool bSpellSelected_)
{
	this->bSpellSelected = bSpellSelected_;
}

AGameCharacter* UBaseSpellComponent::GetSpellCaster() const
{
	return SpellCaster;
}

void UBaseSpellComponent::SetSpellCaster(AGameCharacter* SpellCaster_)
{
	this->SpellCaster = SpellCaster_;
}

FName UBaseSpellComponent::GetName() const
{
	return Name;
}

void UBaseSpellComponent::SetName(const FName& Name_)
{
	this->Name = Name_;
}

UTexture* UBaseSpellComponent::GetIcon() const
{
	return Icon;
}

void UBaseSpellComponent::SetIcon(UTexture* Icon_)
{
	this->Icon = Icon_;
}

