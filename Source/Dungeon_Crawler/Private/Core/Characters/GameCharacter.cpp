// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/GameCharacter.h"
#include "Core/HexMapSystem/HexCell.h"
#include "Core/Characters/CharacterInfo/CharacterInfo.h"
#include "AIControllers/CharacterAIController.h"
#include "Core/Characters/CharacterComponents/HealthComponent.h"
#include "Core/DamageTypes/BaseDamageType.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	if (!AIControllerClass->IsChildOf(ACharacterAIController::StaticClass()))
	{
		AIControllerClass = ACharacterAIController::StaticClass();
		SpawnDefaultController();
	}
	Super::BeginPlay();
	if (UWorld* World= GetWorld())
	{
		FHitResult HitResult;
		World->LineTraceSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() - FVector::UpVector*100, ECollisionChannel::ECC_Visibility);
		if(AHexCell* HexCell = Cast<AHexCell>(HitResult.GetActor()))
		{
			HexLocation = HexCell;
			FVector NewLocation;
			NewLocation.X = HexLocation->GetActorLocation().X;
			NewLocation.Y = HexLocation->GetActorLocation().Y;
			NewLocation.Z = GetActorLocation().Z;
			SetActorLocation(NewLocation);
			HexGrid = HexLocation->GetParentHexGrid();
			HexLocation->SetOccupierCharacter(this);
		}
	}
}


float AGameCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (UBaseDamageType* const DamageType = Cast<UBaseDamageType>(DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : nullptr))
	{
		return HealthComponent->TakeDamage(DamageAmount, DamageType);
	}
	return 0;
}

void AGameCharacter::MoveStraightToCell(AHexCell* Destination)
{
	Cast<ACharacterAIController>(GetController())->MoveStraightToCell(Destination);
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


AHexCell* AGameCharacter::GetHexLocation() const
{
	return HexLocation;
}

AHexGrid* AGameCharacter::GetHexGrid() const
{
	return HexGrid;
}

EMovementState AGameCharacter::GetMovementState() const
{
	return MovementState;
}

//Character RHI_WANT_RESOURCE_INFO

int AGameCharacter::GetSpeed()
{
	return CharacterInfo->GetSpeed();
}

int AGameCharacter::GetMaxHealth()
{
	return CharacterInfo->GetBaseHealth();
}

int AGameCharacter::GetPhysicProtection()
{
	return CharacterInfo->GetPhysicProtection();
}

int AGameCharacter::GetMagicProtection()
{
	return CharacterInfo->GetMagicProtection();
}

int AGameCharacter::GetAttack()
{
	return CharacterInfo->GetAttack();
}

int AGameCharacter::GetAttackLesser()
{
	return CharacterInfo->GetAttackLesser();
}

int AGameCharacter::GetAttackGreater()
{
	return CharacterInfo->GetAttackGreater();
}

int AGameCharacter::GetPrecision()
{
	return CharacterInfo->GetPrecision();
}

int AGameCharacter::GetCriticalChances()
{
	return CharacterInfo->GetCriticalChances();
}

int AGameCharacter::DodgeChances()
{
	return CharacterInfo->GetDodgeChance();
}
