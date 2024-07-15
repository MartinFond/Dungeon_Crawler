// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDamageType.h"
#include "PhysicalDamage.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DUNGEON_CRAWLER_API UPhysicalDamage : public UBaseDamageType
{
	GENERATED_BODY()

public:
	virtual int ProcessDamages(int Damage, AGameCharacter* Receiver) const override;
 
};
