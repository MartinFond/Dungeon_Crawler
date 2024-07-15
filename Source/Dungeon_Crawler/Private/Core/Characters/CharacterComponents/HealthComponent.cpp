// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/CharacterComponents/HealthComponent.h"

#include "Core/Characters/GameCharacter.h"
#include "Core/DamageTypes/BaseDamageType.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<AGameCharacter>(GetOwner());
	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!bInitialized)
	{
		MaxHealth = OwnerCharacter->GetMaxHealth();
		CurrentHealth = MaxHealth;
		bInitialized = true;
	}
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

int UHealthComponent::TakeDamage(int Damage,const UBaseDamageType* DamageType)
{
	int FinalDamage = DamageType->ProcessDamages(Damage, Cast<AGameCharacter>(GetOwner()));
	CurrentHealth -= FinalDamage;
	if (CurrentHealth < 0)
	{
		CurrentHealth =0;
	}
	return FinalDamage;
}

