// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/EnemyGameCharacter.h"
#include "Core/Characters/CharacterInfo/CharacterInfo.h"
#include "GameModes/DungeonGameMode.h"
#include "Kismet/GameplayStatics.h"

void AEnemyGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	ADungeonGameMode* GameMode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(World));
	GameMode->AddEnemy(this);
	
	CharacterInfo = Cast<UCharacterInfo>(AddComponentByClass(CharacterInfoType, false, FTransform::Identity, false));
	this->AddInstanceComponent(CharacterInfo);
	this->AddOwnedComponent(CharacterInfo);
	FString* RowNameString =new FString(StaticEnum<EEnemyType>()->GetValueAsString(EnemyType));
	RowNameString->Split("::", nullptr, RowNameString);
	FName RowName = FName(*RowNameString);
	FCharacterInfoRow* CharacterInfoRow = EnemyTypeDataTable->FindRow<FCharacterInfoRow>(RowName, "");

	CharacterInfo->LoadCharacterInfoRow(*CharacterInfoRow);
}
