// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Characters/CharacterComponents/BaseSpellComponent.h"
#include "SingleTargetSpellComponent.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_CRAWLER_API USingleTargetSpellComponent : public UBaseSpellComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool SetHoveredSpellTarget();

protected:

	UPROPERTY(BlueprintReadWrite)
	AGameCharacter* SpellTarget;

	UFUNCTION(BlueprintCallable)
	bool CheckRangeSingle();
	UFUNCTION(BlueprintCallable)
	bool CheckHitSingle();
	

	//Getters & Setters
public:
	[[nodiscard]] AGameCharacter* GetSpellTarget() const;
	void SetSpellTarget(AGameCharacter* SpellTarget);
};
