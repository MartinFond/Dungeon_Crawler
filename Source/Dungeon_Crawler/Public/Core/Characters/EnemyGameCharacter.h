// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Characters/GameCharacter.h"
#include "EnemyGameCharacter.generated.h"


struct FCharacterInfoRow;

UENUM()
enum class EEnemyType : uint8
{
	Invalid,
	Skeleton,
	Max UMETA(HIDDEN)
};

/**
 * 
 */
UCLASS()
class DUNGEON_CRAWLER_API AEnemyGameCharacter : public AGameCharacter
{
	GENERATED_BODY()
	virtual void BeginPlay() override;


protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	EEnemyType EnemyType;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UDataTable* EnemyTypeDataTable;
};
