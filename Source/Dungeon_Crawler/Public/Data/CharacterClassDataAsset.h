// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RenderResource.h"
#include "CharacterClassDataAsset.generated.h"


enum class EClass : uint8;
class UBaseSpellComponent;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FCharacterClassData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseSpellComponent> Spell;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture* SpellIcon;
};

USTRUCT(BlueprintType)
struct FCharacterClassesData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCharacterClassData> Spells;
	
};

UCLASS(BlueprintType)
class DUNGEON_CRAWLER_API UCharacterClassDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EClass, FCharacterClassesData> Classes;

public:
	[[nodiscard]] TMap<EClass, FCharacterClassesData> GetClasses() const;
	void SetClasses(const TMap<EClass, FCharacterClassesData>& Classes);
};
