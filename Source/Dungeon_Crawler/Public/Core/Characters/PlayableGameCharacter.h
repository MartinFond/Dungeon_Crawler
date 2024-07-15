// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Characters/GameCharacter.h"
#include "PlayableGameCharacter.generated.h"

# define SPELL_NUMBER 4

class UBaseSpellComponent;
class UCharacterClassDataAsset;
/**
 * 
 */
UENUM()
enum class EClassFamily : uint8
{
	Invalid,
	Martial,
	Arcane,
	Holy,
	Nature,
	Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EClass : uint8
{
	Invalid,
	Martial_Apprentice,
	Arcane_Apprentice,
	Divine_Apprentice,
	Nature_Apprentice,

	Warrior,
	Rogue,
	Ranger,
	Doctor,

	Wizard,
	Bard,
	Warlock,
	BattleMage,

	Priest,
	Paladin,
	ShadowPriest,
	FallenPaladin,

	Druid,
	Shaman,
	Barbarian,
	Tracker,
	
	Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ERace : uint8
{
	Invalid,
	Human,
	Elf,
	Halfling,
	Dwarf,
	Max
};

UCLASS(BlueprintType)
class DUNGEON_CRAWLER_API APlayableGameCharacter : public AGameCharacter
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	//Public Methods
public:
	
	//Attributes
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EClass Class;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ERace Race;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EClassFamily ClassFamily;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Level;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UDataTable* RaceDataTable;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UDataTable* ClassDataTable;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UCharacterClassDataAsset* ClassDataAsset;
	UPROPERTY(BlueprintReadWrite)
	TArray<UBaseSpellComponent*> Spells;
	UPROPERTY(BlueprintReadWrite)
	TArray<UBaseSpellComponent*> SelectedSpells;

	
	
	//Getters & Setters
public:

};
