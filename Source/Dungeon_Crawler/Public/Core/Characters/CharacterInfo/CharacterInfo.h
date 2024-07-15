// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterInfo.generated.h"

/**
 * 
 */

USTRUCT(Blueprintable)
struct FCharacterInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int AttackLesser;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int AttackGreater;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int Attack;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int PhysicProtection;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int MagicProtection;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int BaseHealth;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int Precision;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int CriticalChances;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int DodgeChance;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int Initiative;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int Speed;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int BleedResistance;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int FireResistance;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int PoisonResistance;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int ControlResistance;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int DeathResistance;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int StorageCount;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int Perception;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int LockPickingChances;
	
};

UCLASS(Blueprintable, BlueprintType)
class DUNGEON_CRAWLER_API UCharacterInfo : public UActorComponent
{
	GENERATED_BODY()
	//Public Methods
public:
	UFUNCTION(BlueprintCallable)
	void LoadCharacterInfoRow(FCharacterInfoRow CharacterInfoRow);
	//Attributes
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int AttackLesser = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int AttackGreater = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int Attack = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int PhysicProtection = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int MagicProtection = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int BaseHealth = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int Precision = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int CriticalChances = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int DodgeChance = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int Initiative = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int Speed = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int BleedResistance = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int FireResistance = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int PoisonResistance = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int ControlResistance = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int DeathResistance = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int StorageCount = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int Perception = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int LockPickingChances = 0;

	

public:
	


	//Getters & Setters
	[[nodiscard]] int GetAttackLesser() const
	{
		return AttackLesser;
	}

	[[nodiscard]] int GetAttackGreater() const
	{
		return AttackGreater;
	}
	
	[[nodiscard]] int GetAttack() const
	{
		return Attack;
	}
	
	[[nodiscard]] int GetPhysicProtection() const
	{
		return PhysicProtection;
	}

	void SetPhysicProtection(int PhysicProtection_)
	{
		this->PhysicProtection = PhysicProtection_;
	}

	[[nodiscard]] int GetMagicProtection() const
	{
		return MagicProtection;
	}

	void SetMagicProtection(int MagicProtection_)
	{
		this->MagicProtection = MagicProtection_;
	}

	[[nodiscard]] int GetBaseHealth() const
	{
		return BaseHealth;
	}

	void SetBaseHealth(int BaseHealth_)
	{
		this->BaseHealth = BaseHealth_;
	}

	[[nodiscard]] int GetPrecision() const
	{
		return Precision;
	}

	void SetPrecision(int Precision_)
	{
		this->Precision = Precision_;
	}

	[[nodiscard]] int GetCriticalChances() const
	{
		return CriticalChances;
	}

	void SetCriticalChances(int CriticalChances_)
	{
		this->CriticalChances = CriticalChances_;
	}

	[[nodiscard]] int GetDodgeChance() const
	{
		return DodgeChance;
	}

	void SetDodgeChance(int DodgeChance_)
	{
		this->DodgeChance = DodgeChance_;
	}

	[[nodiscard]] int GetInitiative() const
	{
		return Initiative;
	}

	void SetInitiative(int Initiative_)
	{
		this->Initiative = Initiative_;
	}

	[[nodiscard]] int GetSpeed() const
	{
		return Speed;
	}

	void SetSpeed(int Speed_)
	{
		this->Speed = Speed_;
	}

	[[nodiscard]] int GetBleedResistance() const
	{
		return BleedResistance;
	}

	void SetBleedResistance(int BleedResistance_)
	{
		this->BleedResistance = BleedResistance_;
	}

	[[nodiscard]] int GetFireResistance() const
	{
		return FireResistance;
	}

	void SetFireResistance(int FireResistance_)
	{
		this->FireResistance = FireResistance_;
	}

	[[nodiscard]] int GetPoisonResistance() const
	{
		return PoisonResistance;
	}

	void SetPoisonResistance(int PoisonResistance_)
	{
		this->PoisonResistance = PoisonResistance_;
	}

	[[nodiscard]] int GetControlResistance() const
	{
		return ControlResistance;
	}

	void SetControlResistance(int ControlResistance_)
	{
		this->ControlResistance = ControlResistance_;
	}

	[[nodiscard]] int GetDeathResistance() const
	{
		return DeathResistance;
	}

	void SetDeathResistance(int DeathResistance_)
	{
		this->DeathResistance = DeathResistance_;
	}

	[[nodiscard]] int GetStorageCount() const
	{
		return StorageCount;
	}

	void SetStorageCount(int StorageCount_)
	{
		this->StorageCount = StorageCount_;
	}

	[[nodiscard]] int GetPerception() const
	{
		return Perception;
	}

	void SetPerception(int Perception_)
	{
		this->Perception = Perception_;
	}

	[[nodiscard]] int GetLockPickingChances() const
	{
		return LockPickingChances;
	}

	void SetLockPickingChances(int LockPickingChances_)
	{
		this->LockPickingChances = LockPickingChances_;
	}

};

