// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/CharacterInfo/CharacterInfo.h"

void UCharacterInfo::LoadCharacterInfoRow(FCharacterInfoRow CharacterInfoRow)
{
	AttackLesser +=CharacterInfoRow.AttackLesser;
	AttackGreater +=CharacterInfoRow.AttackGreater;
	Attack += CharacterInfoRow.Attack;
	PhysicProtection += CharacterInfoRow.PhysicProtection;
	MagicProtection += CharacterInfoRow.PhysicProtection;
	BaseHealth += CharacterInfoRow.BaseHealth;
	Precision += CharacterInfoRow.Precision;
	CriticalChances += CharacterInfoRow.CriticalChances;
	DodgeChance += CharacterInfoRow.DodgeChance;
	Initiative += CharacterInfoRow.Initiative;
	Speed += CharacterInfoRow.Speed;
	BleedResistance += CharacterInfoRow.BleedResistance;
	FireResistance += CharacterInfoRow.FireResistance;
	PoisonResistance += CharacterInfoRow.PoisonResistance;
	ControlResistance += CharacterInfoRow.ControlResistance;
	DeathResistance += CharacterInfoRow.DeathResistance;
	StorageCount += CharacterInfoRow.StorageCount;
	Perception += CharacterInfoRow.Perception;
	LockPickingChances += CharacterInfoRow.LockPickingChances;
}
