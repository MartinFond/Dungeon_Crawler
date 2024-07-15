// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/CharacterComponents/SingleTargetSpellComponent.h"

#include "Core/HexMapSystem/HexCell.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/DungeonPlayerController.h"

bool USingleTargetSpellComponent::SetHoveredSpellTarget()
{
	return ((SpellTarget = Cast<ADungeonPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetOveredCell()->GetOccupierCharacter()) != nullptr);
}

bool USingleTargetSpellComponent::CheckRangeSingle()
{
	return Super::CheckRange(SpellTarget);
}

bool USingleTargetSpellComponent::CheckHitSingle()
{
	return Super::CheckHit(SpellTarget);
}


AGameCharacter* USingleTargetSpellComponent::GetSpellTarget() const
{
	return SpellTarget;
}

void USingleTargetSpellComponent::SetSpellTarget(AGameCharacter* SpellTarget_)
{
	this->SpellTarget = SpellTarget_;
}
