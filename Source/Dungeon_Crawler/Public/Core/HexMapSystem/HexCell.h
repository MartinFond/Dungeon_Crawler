// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OverlayTile.h"
#include "GameFramework/Actor.h"
#include "HexCell.generated.h"

class AGameCharacter;
class UOverlayTile;
class AHexGrid;
class UHexTile;

USTRUCT(Blueprintable)
struct FCoordinates
{
	GENERATED_BODY()
	float First;
	float Second;

	static FCoordinates OffsetToAxial(const FCoordinates OffsetCoordinates);
};

UCLASS()
class DUNGEON_CRAWLER_API AHexCell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexCell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;
	void Initialize();

	UFUNCTION()
	void CustomOnBeginMouseOver(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void CustomOnEndMouseOver(UPrimitiveComponent* TouchedComponent);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Public methods
	UFUNCTION()
	void OnBuildMap();
	UFUNCTION()
	static FIntPoint OffsetToAxial(FIntPoint OffsetCoordinates);
	UFUNCTION(BlueprintCallable)
	TArray<AHexCell*> GetNeighbors();
	UFUNCTION(BlueprintCallable)
	double Distance(const AHexCell* HexCell) const;
	UFUNCTION(BlueprintCallable)
	int GetMovementCost(EMovementState MovementState) const;
	UFUNCTION(BlueprintCallable)
	void ShowOverlayTile();
	UFUNCTION(BlueprintCallable)
	void HideOverlayTile();
	UFUNCTION(BlueprintCallable)
	void SetOverlayTileGreen();
	UFUNCTION(BlueprintCallable)
	void SetOverlayTileRed();
	
	//Editor Methods
	UFUNCTION(BlueprintCallable, CallInEditor, Category="HexCell")
	void SwitchTileType();
	UFUNCTION(BlueprintCallable, CallInEditor, Category="HexCell|Debug")
	void PrintAxialCoordinates();
	UFUNCTION(BlueprintCallable, CallInEditor, Category="HexCell|Debug")
	void PrintOffSetCoordinates();

	

protected:
	UPROPERTY(BlueprintReadWrite)
	FIntPoint OffsetCoordinates;
	UPROPERTY(BlueprintReadWrite)
	FIntPoint AxialCoordinates;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UHexTile> HexTileType;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	AGameCharacter* OccupierCharacter;

public:
	[[nodiscard]] AGameCharacter* GetOccupierCharacter() const;
	void SetOccupierCharacter(AGameCharacter* OccupierCharacter);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HexCell")
	UHexTile* HexTile;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="HexCell")
	AHexGrid* ParentHexGrid;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UOverlayTile> OverlayTileType;
	UPROPERTY(BlueprintReadWrite)
	UOverlayTile* OverlayTile;

	UPROPERTY(BlueprintReadWrite)
	bool bMouseOvered;
	
	//PostInitialisation
	UPROPERTY(BlueprintReadOnly)
	bool bPostInitialized;

public:

	//Getters & Setters
	[[nodiscard]] FIntPoint GetOffsetCoordinates() const;
	void SetOffsetCoordinates(const FIntPoint& OffsetCoordinates);
	[[nodiscard]] FIntPoint GetAxialCoordinates() const;
	void SetAxialCoordinates(const FIntPoint& AxialCoordinates);

	
	[[nodiscard]] bool IsEmpty() const;

	[[nodiscard]] AHexGrid* GetParentHexGrid() const;
	void SetParentHexGrid(AHexGrid* ParentHexGrid_);

	[[nodiscard]] bool IsObstacle() const;

	void SetPostInitialized(bool bPostInitialized);

	void SetMouseOvered(bool bMouseOvered);


	UFUNCTION(BlueprintCallable)
	int GetQ() const;
	UFUNCTION(BlueprintCallable)
	int GetR() const;
	UFUNCTION(BlueprintCallable)
	int GetS() const;
};


