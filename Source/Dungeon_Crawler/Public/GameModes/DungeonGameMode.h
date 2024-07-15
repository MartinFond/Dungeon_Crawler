// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DungeonGameMode.generated.h"

class AGameCharacter;
class APlayableGameCharacter;
class AEnemyGameCharacter;
/**
 * 
 */

//Delegates

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndTurnSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginTurnSignature);

UCLASS()
class DUNGEON_CRAWLER_API ADungeonGameMode : public AGameMode
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintCallable)
	void SetNextActiveCharacter();

public:
	UFUNCTION(BlueprintCallable)
	void AddEnemy(AEnemyGameCharacter* Enemy);
	UFUNCTION(BlueprintCallable)
	void AddAlly(APlayableGameCharacter* Ally);

	UFUNCTION(BlueprintCallable)
	void EndTurn();
	UFUNCTION(BlueprintCallable)
	void BeginTurn();

	
protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<AEnemyGameCharacter*> Enemies;
	UPROPERTY(BlueprintReadWrite)
	TArray<APlayableGameCharacter*> Allies;
	UPROPERTY(BlueprintReadWrite)
	TArray<AGameCharacter*> Characters;
	UPROPERTY(BlueprintReadWrite)
	AGameCharacter* CurrentActiveCharacter;
	UPROPERTY(BlueprintReadWrite)
	int CurrentActiveCharacterIndex;
	

public:

	//Delegates
	UPROPERTY(BlueprintAssignable)
	FEndTurnSignature EndTurnDelegate;
	UPROPERTY(BlueprintAssignable)
	FEndTurnSignature BeginTurnDelegate;

	//Getters & Setters
	[[nodiscard]] TArray<AEnemyGameCharacter*> GetEnemies() const;
	void SetEnemies(const TArray<AEnemyGameCharacter*>& Enemies);
	[[nodiscard]] TArray<APlayableGameCharacter*> GetAllies() const;
	void SetAllies(const TArray<APlayableGameCharacter*>& Allies);
	[[nodiscard]] TArray<AGameCharacter*> GetCharacters() const;
	void SetCharacters(const TArray<AGameCharacter*>& Characters);
	[[nodiscard]] AGameCharacter* GetCurrentActiveCharacter() const;
};
