// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HexTile.generated.h"

enum class EMovementState : uint8;

UENUM()
enum class EHexTileType : uint8
{	
	Invalid,
	Stone,
	Obstacle,
	Max UMETA(Hidden),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class DUNGEON_CRAWLER_API UHexTile : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHexTile();

	int GetMovementCost(EMovementState MovementState);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EHexTileType HexTileType;

public:
	[[nodiscard]] EHexTileType GetHexTileType() const;
};
