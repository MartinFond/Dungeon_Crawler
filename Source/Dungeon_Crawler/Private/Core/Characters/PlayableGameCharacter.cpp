// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/PlayableGameCharacter.h"

#include "Core/Characters/CharacterComponents/BaseSpellComponent.h"
#include "Core/Characters/CharacterInfo/CharacterInfo.h"
#include "Data/CharacterClassDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/DungeonPlayerController.h"
#include "GameModes/DungeonGameMode.h"

void APlayableGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	ADungeonPlayerController* PlayerController = Cast<ADungeonPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
	PlayerController->SetCharacterControlled(this);

	ADungeonGameMode* GameMode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(World));
	GameMode->AddAlly(this);
	
	CharacterInfo = Cast<UCharacterInfo>(AddComponentByClass(CharacterInfoType, false, FTransform::Identity, false));
	this->AddInstanceComponent(CharacterInfo);
	this->AddOwnedComponent(CharacterInfo);
	
	FString* RaceRowNameString =new FString(StaticEnum<ERace>()->GetValueAsString(Race));
	RaceRowNameString->Split("::", nullptr, RaceRowNameString);
	FName RaceRowName = FName(*RaceRowNameString);
	FCharacterInfoRow* RaceCharacterInfoRow = RaceDataTable->FindRow<FCharacterInfoRow>(RaceRowName, "");
	CharacterInfo->LoadCharacterInfoRow(*RaceCharacterInfoRow);

	FString* ClassRowNameString =new FString(StaticEnum<EClass>()->GetValueAsString(Class));
	ClassRowNameString->Split("::", nullptr, ClassRowNameString);
	FName ClassRowName = FName(*ClassRowNameString);
	FCharacterInfoRow* ClassCharacterInfoRow = ClassDataTable->FindRow<FCharacterInfoRow>(ClassRowName, "");
	CharacterInfo->LoadCharacterInfoRow(*ClassCharacterInfoRow);
	
	FCharacterClassesData ClassesData =  ClassDataAsset->GetClasses()[Class];
	for (auto SpellClass : ClassesData.Spells)
	{
		UBaseSpellComponent* spell = NewObject<UBaseSpellComponent>(this, SpellClass.Spell, SpellClass.Name);
		spell->SetName(SpellClass.Name);
		if (SpellClass.SpellIcon != nullptr)
		{
			spell->SetIcon(SpellClass.SpellIcon);
		}
		Spells.Add(spell);
		spell->RegisterComponent();
		AddInstanceComponent(spell);
		AddOwnedComponent(spell);
	}

	SelectedSpells.SetNum(SPELL_NUMBER);
}

