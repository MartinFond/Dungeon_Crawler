// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DamageTypes/PhysicalDamage.h"

#include "Core/Characters/GameCharacter.h"

int UPhysicalDamage::ProcessDamages(int Damage, AGameCharacter* Receiver) const
{
	int EffectiveDamages = Damage - round(Damage * Receiver->GetPhysicProtection() / 100);
	return EffectiveDamages;
}
