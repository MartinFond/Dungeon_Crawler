// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/DungeonPlayerController.h"

#include "AIController.h"
#include "AIControllers/CharacterAIController.h"
#include "Core/Characters/PlayableGameCharacter.h"
#include "Core/Characters/CharacterComponents/BaseSpellComponent.h"
#include "Core/HexMapSystem/HexCell.h"
#include "Core/HexMapSystem/HexGrid.h"


void ADungeonPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(true);
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));	
}

void ADungeonPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (TurnState == ETurnState::Movement)
	{
		TickMovementState();
	}
	
}

void ADungeonPlayerController::TickMovementState()
{
	TArray<AActor*> AttachedActors;
	HexGrid->GetAttachedActors(AttachedActors);
	for (auto* Actor : AttachedActors)
	{
		if (AHexCell* HexCell = Cast<AHexCell>(Actor))
		{
			HexCell->HideOverlayTile();
		}
	}
	if (!Cast<ACharacterAIController>(CharacterControlled->GetController())->IsMoving() && OveredCell != nullptr)
	{
		TArray<AHexCell*> PathPreview = HexGrid->AStarPath(CharacterControlled->GetHexLocation(), OveredCell, CharacterControlled->GetMovementState());
		int Distance = 0;
		PathPreview.RemoveAt(0);
		for(AHexCell* HexCell : PathPreview)
		{
			Distance += HexCell->GetMovementCost(CharacterControlled->GetMovementState());
			if (Distance > MovementLeft)
			{
				HexCell->SetOverlayTileRed();
			}
			else
			{
				HexCell->SetOverlayTileGreen();
			}
			HexCell->ShowOverlayTile();
		}
	}
}

void ADungeonPlayerController::AStarMove(AHexCell* Destination)
{
	if (MovementLeft == 0)
	{
		return;
	}
	Cast<ACharacterAIController>(CharacterControlled->GetController())->AStarMove(Destination, MovementLeft);
	HexGrid->HideOverlayTiles();
}

void ADungeonPlayerController::OnAction()
{
	switch (TurnState)
	{
	case ETurnState::Invalid:
		break;
	case ETurnState::PlayerTurn:
		break;
	case ETurnState::CastingSpell:
		SelectedSpell->CastSpell();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("CastingSpell!"));	
		break;
	case ETurnState::Movement:
		AStarMove(OveredCell);
		break;
	case ETurnState::EnemyTurn:
		break;
	case ETurnState::Max:
		break;
	}
}

void ADungeonPlayerController::MoveStraightToCell(AHexCell* Destination)
{
	CharacterControlled->MoveStraightToCell(Destination);
}

void ADungeonPlayerController::OnTurnStart()
{
	MovementLeft = CharacterControlled->GetSpeed();
}

//Getters & Setters

int ADungeonPlayerController::GetMovementLeft() const
{
	return MovementLeft;
}

UBaseSpellComponent* ADungeonPlayerController::GetSelectedSpell() const
{
	return SelectedSpell;
}

void ADungeonPlayerController::SetSelectedSpell(UBaseSpellComponent* SelectedSpell_)
{
	this->SelectedSpell = SelectedSpell_;
}

void ADungeonPlayerController::SetMovementLeft(int MovementLeft_)
{
	this->MovementLeft = MovementLeft_;
}

ETurnState ADungeonPlayerController::GetTurnState() const
{
	return TurnState;
}

void ADungeonPlayerController::SetTurnState(ETurnState TurnState_)
{
	this->TurnState = TurnState_;
}

APlayableGameCharacter* ADungeonPlayerController::GetCharacterControlled() const
{
	return CharacterControlled;
}

AHexCell* ADungeonPlayerController::GetOveredCell() const
{
	return OveredCell;
}

AHexGrid* ADungeonPlayerController::GetHexGrid() const
{
	return HexGrid;
}

void ADungeonPlayerController::SetCharacterControlled(APlayableGameCharacter* CharacterControlled_)
{
	this->CharacterControlled = CharacterControlled_;
}

void ADungeonPlayerController::SetOveredCell(AHexCell* OveredCell_)
{
	this->OveredCell = OveredCell_;
}

void ADungeonPlayerController::SetHexGrid(AHexGrid* HexGrid_)
{
	this->HexGrid = HexGrid_;
}
