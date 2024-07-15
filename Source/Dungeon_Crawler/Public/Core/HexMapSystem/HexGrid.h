// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexCell.h"
#include "GameFramework/Actor.h"


#include "HexGrid.generated.h"

class AHexCell;

struct HexPriority
{
	HexPriority(double Priority, AHexCell* HexCell): Priority(Priority), HexCell(HexCell){}
	double Priority;
	AHexCell* HexCell;
};

struct HexPriorityPredicate
{
	bool operator()(const HexPriority& A, const HexPriority& B) const
	{
		// Inverted compared to std::priority_queue - higher priorities float to the top
		return A.Priority < B.Priority;
	}
};


UCLASS(Blueprintable)
class DUNGEON_CRAWLER_API AHexGrid : public AActor
{
public:
	[[nodiscard]] float GetSpacingX() const;
	[[nodiscard]] float GetSpacingY() const;

private:
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AHexGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	void UnStoreHexTile(const FIntPoint OffsetCoordinates);
	void SpawnTile(const FIntPoint OffsetCoordinates, UWorld* World);
	void MoveXPositive();
	void MoveXNegative();
	void MoveYPositive();
	void MoveYNegative();

	//LinePath
	float Lerp(float FirstCell, float LastCell, float Step) const;
	FCoordinates CubeLerp(AHexCell* FirstCell, AHexCell* LastCell, float Step) const;
	AHexCell* CubeRound(FCoordinates floatCoordinates) const;

public:	
	

	UFUNCTION(BlueprintCallable, CallInEditor, Category="HexGrid")
	void BuildMap();
	UFUNCTION(BlueprintCallable, CallInEditor, Category="HexGrid|Dangerous")
	void ClearMap();
	UFUNCTION()
	void Initialize();
	UFUNCTION(BlueprintCallable, CallInEditor, Category="HexGrid|Move")
	void MoveX();
	UFUNCTION(BlueprintCallable, CallInEditor, Category="HexGrid|Move")
	void MoveY();
	UFUNCTION(BlueprintCallable)
	int Distance(const AHexCell* HexCell1, const AHexCell* HexCell2) const;
	UFUNCTION(BlueprintCallable)
	AHexCell* GetCell(int Tq, int Tr) const;
	UFUNCTION(BlueprintCallable)
	TArray<AHexCell*> GetCellNeighbors(const AHexCell* HexCell) const;
	UFUNCTION(BlueprintCallable)
	TArray<AHexCell*> AStarPath(AHexCell* StartingCell, AHexCell* EndCell,const EMovementState MovementState) const;
	UFUNCTION(BlueprintCallable)
	TArray<AHexCell*> LinePath(AHexCell* StartingCell, AHexCell* EndCell) const;

	void StoreHexTile(AHexCell* HexTile);

	UFUNCTION(BlueprintCallable)
	void HideOverlayTiles();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bInitialized;

public:
	[[nodiscard]] bool IsInitialized() const;
	void SetInitialized(bool bInitialized);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ClampMin=0))
	int X;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ClampMin=0))
	int Y;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SpacingX;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SpacingY;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Offset;

public:
	[[nodiscard]] float GetOffset() const;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AHexCell> HexCellType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="HexGrid|Move")
	int XMoveValue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="HexGrid|Move")
	int YMoveValue;

	TArray<TArray<AHexCell*>> HexMapArray;
};

