// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CharacterClassDataAsset.h"

TMap<EClass, FCharacterClassesData> UCharacterClassDataAsset::GetClasses() const
{
	return Classes;
}

void UCharacterClassDataAsset::SetClasses(const TMap<EClass, FCharacterClassesData>& Classes_)
{
	this->Classes = Classes_;
}
