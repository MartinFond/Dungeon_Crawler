// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DungeonPlayerController.generated.h"

class UBaseSpellComponent;
enum class EMovementState : uint8;
class AHexGrid;
class AHexCell;
class APlayableGameCharacter;
/**
 * 
 */

UENUM(BlueprintType)
enum class ETurnState : uint8
{
	Invalid,
	PlayerTurn,
	CastingSpell,
	Movement,
	EnemyTurn,
	Max UMETA(Hidden)
};

UCLASS()
class DUNGEON_CRAWLER_API ADungeonPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	//Public Methods
public:
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
	void MoveStraightToCell(AHexCell* Destination);
	UFUNCTION(BlueprintCallable)
	void OnTurnStart();

	//Protected Methods
protected:
	UFUNCTION()
	void TickMovementState();
	UFUNCTION(BlueprintCallable)
	void AStarMove(AHexCell* Destination);

	UFUNCTION(BlueprintCallable)
	void OnAction();
	
	//Attributes
protected:
	UPROPERTY(BlueprintReadWrite)
	APlayableGameCharacter* CharacterControlled;
	UPROPERTY(BlueprintReadWrite)
	AHexCell* OveredCell;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	AHexGrid* HexGrid;
	
	UPROPERTY(BlueprintReadWrite)
	ETurnState TurnState;
	UPROPERTY(BlueprintReadWrite)
	UBaseSpellComponent* SelectedSpell;
	UPROPERTY(BlueprintReadWrite)
	int MovementLeft;
	

public:

	//Getters & Setters
	[[nodiscard]] APlayableGameCharacter* GetCharacterControlled() const;
	[[nodiscard]] AHexCell* GetOveredCell() const;
	[[nodiscard]] AHexGrid* GetHexGrid() const;
	[[nodiscard]] int GetMovementLeft() const;
	[[nodiscard]] UBaseSpellComponent* GetSelectedSpell() const;
	[[nodiscard]] ETurnState GetTurnState() const;
	
	void SetCharacterControlled(APlayableGameCharacter* CharacterControlled);
	void SetOveredCell(AHexCell* OveredCell);
	void SetHexGrid(AHexGrid* HexGrid);
	void SetMovementLeft(int MovementLeft);
	void SetSelectedSpell(UBaseSpellComponent* SelectedSpell);
	void SetTurnState(ETurnState TurnState);
};


