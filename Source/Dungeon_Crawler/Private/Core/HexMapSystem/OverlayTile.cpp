// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HexMapSystem/OverlayTile.h"

void UOverlayTile::SetGreen()
{
	SetMaterial(0, GreenMaterial);
}

void UOverlayTile::SetRed()
{
	SetMaterial(0, RedMaterial);
}
