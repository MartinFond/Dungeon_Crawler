// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


class AGameCharacter;
class UBaseDamageType;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class DUNGEON_CRAWLER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	int TakeDamage(int Damage, const UBaseDamageType* DamageType);

	//Attributes
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int MaxHealth;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int CurrentHealth;

	UPROPERTY(BlueprintReadWrite)
	AGameCharacter* OwnerCharacter;

	bool bInitialized = false;
};
