// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

class UHealthComponent;
class AHexCell;
class UCharacterInfo;
class AHexGrid;

UENUM()
enum class EMovementState : uint8
{
	Invalid,
	Walking,
	Flying,
	Spell,
	Max UMETA(Hidden)
};
//Deleagates

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDamageTakenSignature, int, Damage, bool, Critic, bool, Missed);

UCLASS()
class DUNGEON_CRAWLER_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void MoveStraightToCell(AHexCell* Destination);

	UFUNCTION(BlueprintCallable)
	virtual int GetSpeed();
	UFUNCTION(BlueprintCallable)
	virtual int GetMaxHealth();
	UFUNCTION(BlueprintCallable)
	virtual int GetPhysicProtection();
	UFUNCTION(BlueprintCallable)
	virtual int GetMagicProtection();
	UFUNCTION(BlueprintCallable)
	virtual int GetAttack();
	UFUNCTION(BlueprintCallable)
	virtual int GetAttackLesser();
	UFUNCTION(BlueprintCallable)
	virtual int GetAttackGreater();
	UFUNCTION(BlueprintCallable)
	virtual int GetPrecision();
	UFUNCTION(BlueprintCallable)
	virtual int GetCriticalChances();
	UFUNCTION(BlueprintCallable)
	virtual int DodgeChances();
	
//Delegates

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDamageTakenSignature OnDamageTakenDelegate;

	
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Character|Stats")
	TSubclassOf<UCharacterInfo> CharacterInfoType;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	AHexCell* HexLocation;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	AHexGrid* HexGrid;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	EMovementState MovementState;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Character|Stats")
	UCharacterInfo* CharacterInfo;

	//Components
	UPROPERTY(BlueprintReadWrite)
	UHealthComponent* HealthComponent;
	
	//Getters & Setters
public:
	[[nodiscard]] AHexCell* GetHexLocation() const;
	[[nodiscard]] AHexGrid* GetHexGrid() const;
	[[nodiscard]] EMovementState GetMovementState() const;
	void SetHexLocation(AHexCell* HexLocation);
	void SetMovementState(EMovementState MovementState);

	
	
};

inline void AGameCharacter::SetHexLocation(AHexCell* HexLocation_)
{
	this->HexLocation = HexLocation_;
}

inline void AGameCharacter::SetMovementState(EMovementState MovementState_)
{
	this->MovementState = MovementState_;
}
