// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Characters/CharacterComponents/SingleTargetSpellComponent.h"
#include "WarriorSpell_Impale.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_CRAWLER_API UWarriorSpell_Impale : public USingleTargetSpellComponent
{
	GENERATED_BODY()

	virtual void CastSpell_Implementation() override;
	
};
