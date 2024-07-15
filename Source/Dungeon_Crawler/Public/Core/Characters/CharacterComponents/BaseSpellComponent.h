// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseSpellComponent.generated.h"


class AGameCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class DUNGEON_CRAWLER_API UBaseSpellComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseSpellComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnSelectSpell();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CastSpell();
	UFUNCTION(BlueprintCallable)
	bool CheckHit(AGameCharacter* SpellTarget);
	UFUNCTION(BlueprintCallable)
	bool CheckRange(AGameCharacter* SpellTarget);
	UFUNCTION(BlueprintCallable)
	bool CheckCritic();
	UFUNCTION(BlueprintCallable)
	int GenerateDamage();

protected:
	UPROPERTY(BlueprintReadWrite)
	bool bSpellSelected;
	UPROPERTY(BlueprintReadWrite)
	AGameCharacter* SpellCaster;
	UPROPERTY(BlueprintReadWrite)
	FName Name;
	UPROPERTY(BlueprintReadWrite)
	UTexture* Icon;

	//Stats
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int CriticalChances;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int RangeMin;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int RangeMax;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int DamageRatio;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int Precision;
	

	//Getters & Setters
public:
	[[nodiscard]] bool IsSpellSelected() const;
	void SetSpellSelected(bool bSelected);
	[[nodiscard]] AGameCharacter* GetSpellCaster() const;
	void SetSpellCaster(AGameCharacter* SpellCaster);
	[[nodiscard]] FName GetName() const;
	void SetName(const FName& Name);
	[[nodiscard]] UTexture* GetIcon() const;
	void SetIcon(UTexture* Icon);
};
