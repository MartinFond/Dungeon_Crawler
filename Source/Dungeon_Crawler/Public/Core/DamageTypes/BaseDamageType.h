// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "BaseDamageType.generated.h"

class AGameCharacter;
/**
 * 
 */
UCLASS()
class DUNGEON_CRAWLER_API UBaseDamageType : public UDamageType
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual int ProcessDamages(int Damage, AGameCharacter* Receiver) const;
	
};
