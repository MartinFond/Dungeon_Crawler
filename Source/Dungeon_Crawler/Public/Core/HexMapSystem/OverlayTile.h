// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "OverlayTile.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_CRAWLER_API UOverlayTile : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void SetGreen();
	void SetRed();
	
protected:
	UPROPERTY(EditAnywhere, Category="Material")
	UMaterialInterface* GreenMaterial;
	UPROPERTY(EditAnywhere, Category="Material")
	UMaterialInterface* RedMaterial;
	
};
