// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/DungeonGameMode.h"

#include "PlayerControllers/DungeonPlayerController.h"
#include "Core/Characters/EnemyGameCharacter.h"
#include "Core/Characters/PlayableGameCharacter.h"
#include "Kismet/GameplayStatics.h"

void ADungeonGameMode::BeginPlay()
{

}

void ADungeonGameMode::SetNextActiveCharacter()
{
	if (Characters.IndexOfByKey(CurrentActiveCharacter) == CurrentActiveCharacterIndex)
	{
		CurrentActiveCharacterIndex += 1;
		if (CurrentActiveCharacterIndex >= Characters.Num())
		{
			CurrentActiveCharacterIndex = 0;
		}
	}
	CurrentActiveCharacter = Characters[CurrentActiveCharacterIndex];
	
	ADungeonPlayerController* PlayerController = Cast<ADungeonPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (APlayableGameCharacter* PlayableActiveCharacter = Cast<APlayableGameCharacter>(CurrentActiveCharacter))
	{

		PlayerController->SetCharacterControlled(PlayableActiveCharacter);
		PlayerController->SetTurnState(ETurnState::PlayerTurn);
	}
	else
	{
		PlayerController->SetTurnState(ETurnState::EnemyTurn);
	}
}

void ADungeonGameMode::AddEnemy(AEnemyGameCharacter* Enemy)
{
	Enemies.Add(Enemy);
	Characters.Add(Enemy);
}

void ADungeonGameMode::AddAlly(APlayableGameCharacter* Ally)
{
	Allies.Add(Ally);
	Characters.Add(Ally);
}

void ADungeonGameMode::EndTurn()
{
	EndTurnDelegate.Broadcast();
}

void ADungeonGameMode::BeginTurn()
{
	SetNextActiveCharacter();
	BeginTurnDelegate.Broadcast();
}

TArray<AEnemyGameCharacter*> ADungeonGameMode::GetEnemies() const
{
	return Enemies;
}

void ADungeonGameMode::SetEnemies(const TArray<AEnemyGameCharacter*>& Enemies_)
{
	this->Enemies = Enemies_;
}

TArray<APlayableGameCharacter*> ADungeonGameMode::GetAllies() const
{
	return Allies;
}

void ADungeonGameMode::SetAllies(const TArray<APlayableGameCharacter*>& Allies_)
{
	this->Allies = Allies_;
}

TArray<AGameCharacter*> ADungeonGameMode::GetCharacters() const
{
	return Characters;
}

void ADungeonGameMode::SetCharacters(const TArray<AGameCharacter*>& Characters_)
{
	this->Characters = Characters_;
}

AGameCharacter* ADungeonGameMode::GetCurrentActiveCharacter() const
{
	return CurrentActiveCharacter;
}
