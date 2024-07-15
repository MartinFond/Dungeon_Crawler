// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/DamageTypes/BaseDamageType.h"
#include "BleedDamage.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_CRAWLER_API UBleedDamage : public UBaseDamageType
{
	GENERATED_BODY()

	virtual int ProcessDamages(int Damage, AGameCharacter* Receiver) const override;
	
};
