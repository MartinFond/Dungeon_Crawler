// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/CharacterComponents/SpellComponents/Warrior/WarriorSpell_Impale.h"

#include "Core/Characters/GameCharacter.h"
#include "Core/Characters/CharacterComponents/StatusComponents/StatusComponentBleed.h"
#include "Core/DamageTypes/PhysicalDamage.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/DungeonPlayerController.h"

void UWarriorSpell_Impale::CastSpell_Implementation()
{
	if (!SetHoveredSpellTarget())
	{
		return;
	}
	
	if (!CheckRangeSingle())
	{
		return;
	}

	if (!CheckHitSingle())
	{
		SpellTarget->OnDamageTakenDelegate.Broadcast(0, false, true);
		return;
	}

	int Damage = GenerateDamage();
	bool isCritic = CheckCritic();

	if (isCritic)
	{
		Damage *= 2;
	}

	int AppliedDamage = UGameplayStatics::ApplyDamage(SpellTarget, Damage, nullptr, GetOwner(), UPhysicalDamage::StaticClass());
	SpellTarget->OnDamageTakenDelegate.Broadcast(AppliedDamage, isCritic, false);
	UStatusComponentBleed* BleedComponent = Cast<UStatusComponentBleed>(SpellTarget->AddComponentByClass(UStatusComponentBleed::StaticClass(), false, SpellTarget->GetTransform(), false));
	BleedComponent->SetTurnsLeft(3);
	BleedComponent->SetDamage(2);
	BleedComponent->RegisterComponent();
	
}
