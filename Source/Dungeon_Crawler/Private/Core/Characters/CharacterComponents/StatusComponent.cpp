// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/CharacterComponents/StatusComponent.h"

#include "GameModes/DungeonGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ADungeonGameMode* GameMode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->BeginTurnDelegate.AddDynamic(this, &UStatusComponent::OnTurnBegin);
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatusComponent::OnTurnBegin()
{
}

