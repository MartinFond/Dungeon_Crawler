// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HexMapSystem/HexTile.h"
#include "Core/Characters/GameCharacter.h"

// Sets default values for this component's properties
UHexTile::UHexTile()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

int UHexTile::GetMovementCost(EMovementState MovementState)
{
	return 1;
}


// Called when the game starts
void UHexTile::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHexTile::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EHexTileType UHexTile::GetHexTileType() const
{
	return HexTileType;
}

