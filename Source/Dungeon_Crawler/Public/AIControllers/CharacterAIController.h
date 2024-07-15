// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CharacterAIController.generated.h"

class AGameCharacter;
class AHexCell;
class AHexGrid;
/**
 * 
 */
UCLASS()
class DUNGEON_CRAWLER_API ACharacterAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void MoveStraightToCell(AHexCell* Destination);
	UFUNCTION(BlueprintCallable)
	void AStarMove(AHexCell* Destination, int MovementLeft);
	UFUNCTION(BlueprintCallable)
	void MoveAlongPath();
	UFUNCTION(BlueprintCallable)
	void CustomPathMove(TArray<AHexCell*> Path);

protected:
	UPROPERTY(BlueprintReadWrite)
	AGameCharacter* ControlledCharacter;

	//Movement
	UPROPERTY(BlueprintReadWrite)
	bool bMoving;

public:
	[[nodiscard]] bool IsMoving() const;
	void SetMoving(bool bMoving);

protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<AHexCell*> PathTiles;
	UPROPERTY(BlueprintReadWrite)
	int CurrentTileIndex;
	
	
};
