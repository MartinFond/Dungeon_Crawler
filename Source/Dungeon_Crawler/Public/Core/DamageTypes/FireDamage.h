// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/DamageTypes/BaseDamageType.h"
#include "FireDamage.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_CRAWLER_API UFireDamage : public UBaseDamageType
{
	GENERATED_BODY()

	virtual int ProcessDamages(int Damage, AGameCharacter* Receiver) const override;
	
};
