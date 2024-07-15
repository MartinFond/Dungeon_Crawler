// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Characters/CharacterComponents/StatusComponent.h"
#include "StatusComponentBleed.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_CRAWLER_API UStatusComponentBleed : public UStatusComponent
{
	GENERATED_BODY()

	virtual void OnTurnBegin() override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Damage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int TurnsLeft;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* Instigator;

public:
	[[nodiscard]] int GetDamage() const;
	void SetDamage(int Damage);
	[[nodiscard]] int GetTurnsLeft() const;
	void SetTurnsLeft(int TurnsLeft);
};
