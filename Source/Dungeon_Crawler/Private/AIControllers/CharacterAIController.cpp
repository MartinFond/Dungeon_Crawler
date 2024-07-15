// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllers/CharacterAIController.h"

#include "Core/Characters/GameCharacter.h"
#include "Core/HexMapSystem/HexGrid.h"
#include "Core/HexMapSystem/HexCell.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/DungeonPlayerController.h"


void ACharacterAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledCharacter = Cast<AGameCharacter>(GetPawn());
	PrimaryActorTick.bCanEverTick = false;
}

void ACharacterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (IsMoving())
	{
		MoveAlongPath();
	}
	else
	{
		PrimaryActorTick.bCanEverTick = false;
	}
}

void ACharacterAIController::MoveStraightToCell(AHexCell* Destination)
{
	FVector CharacterLocation = ControlledCharacter->GetActorLocation();
	FVector DestinationLocation = Destination->GetActorLocation();
	FVector DestinationOffset = (DestinationLocation - CharacterLocation);
	DestinationOffset.Normalize();
	DestinationLocation += DestinationOffset * 40;
	MoveToLocation(DestinationLocation);
	ControlledCharacter->GetHexLocation()->SetOccupierCharacter(nullptr);
	ControlledCharacter->SetHexLocation(Destination);
	Destination->SetOccupierCharacter(ControlledCharacter);
}

void ACharacterAIController::AStarMove(AHexCell* Destination, int MovementLeft)
{
	TArray<AHexCell*> FullPathTiles = ControlledCharacter->GetHexGrid()->AStarPath(ControlledCharacter->GetHexLocation(), Destination ,ControlledCharacter->GetMovementState());
	PathTiles.Empty();
	int Distance = 0;
	if (FullPathTiles.IsEmpty())
	{
		return;
	}
	FullPathTiles.RemoveAt(0);
	for (auto Tile : FullPathTiles)
	{
		if (Distance + Tile->GetMovementCost(ControlledCharacter->GetMovementState()) > MovementLeft)
		{
			break;
		}
		Distance += Tile->GetMovementCost(ControlledCharacter->GetMovementState());
		PathTiles.Add(Tile);
		Cast<ADungeonPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetMovementLeft(MovementLeft - Distance);
	}
	if (PathTiles.IsEmpty())
	{
		return;
	}
	MoveStraightToCell(PathTiles[0]);
	CurrentTileIndex = 0;
	SetMoving(true);
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterAIController::MoveAlongPath()
{
	if (PathTiles.IsEmpty())
	{
		return;
	}
	if (!PathTiles.Last()->IsEmpty())
	{
		PathTiles.Pop(true);
		if (PathTiles.IsEmpty())
		{
			return;
		}
	}
	if (CurrentTileIndex >= PathTiles.Num())
	{
		SetMoving(false);
		return;
	}
	if(FVector::Distance(ControlledCharacter->GetActorLocation(), (PathTiles[CurrentTileIndex]->GetActorLocation())) <= 120)
	{
		ControlledCharacter->GetHexLocation()->SetOccupierCharacter(nullptr);
		ControlledCharacter->SetHexLocation(PathTiles[CurrentTileIndex]);
		if (ControlledCharacter->GetHexLocation()->IsEmpty())
		{
			ControlledCharacter->GetHexLocation()->SetOccupierCharacter(ControlledCharacter);
		}
		CurrentTileIndex += 1;
		if (CurrentTileIndex < PathTiles.Num())
		{
			MoveStraightToCell(PathTiles[CurrentTileIndex]);
		}
		else
		{
			SetMoving(false);
		}
	}
}

void ACharacterAIController::CustomPathMove(TArray<AHexCell*> Path)
{
	PathTiles = Path;
	MoveStraightToCell(PathTiles[0]);
	CurrentTileIndex = 0;
	SetMoving(true);
	PrimaryActorTick.bCanEverTick = true;
}

bool ACharacterAIController::IsMoving() const
{
	return bMoving;
}

void ACharacterAIController::SetMoving(bool bMoving_)
{
	this->bMoving = bMoving_;
}
