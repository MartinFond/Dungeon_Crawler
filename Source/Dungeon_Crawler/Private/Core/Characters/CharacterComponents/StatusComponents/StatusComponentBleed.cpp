  // Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/CharacterComponents/StatusComponents/StatusComponentBleed.h"

#include "Core/Characters/GameCharacter.h"
#include "Core/DamageTypes/FireDamage.h"
#include "GameModes/DungeonGameMode.h"
#include "Kismet/GameplayStatics.h"


  void UStatusComponentBleed::OnTurnBegin()
  {
    Super::OnTurnBegin();
    if (Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetCurrentActiveCharacter() != Cast<AGameCharacter>(this->GetOwner()))
    {
      return;
    }
    AGameCharacter* Owner = Cast<AGameCharacter>(GetOwner());
    int AppliedDamage = UGameplayStatics::ApplyDamage(
      Owner,
      Damage,
      UGameplayStatics::GetPlayerController(GetWorld(),
        0),
        Instigator,UFireDamage::StaticClass()
        );
    Owner->OnDamageTakenDelegate.Broadcast(AppliedDamage, false, false);
    TurnsLeft -= 1;
    if (TurnsLeft <= 0)
    {
    DestroyComponent();
    }
  }

  int UStatusComponentBleed::GetDamage() const
  {
    return Damage;
  }

  void UStatusComponentBleed::SetDamage(int Damage_)
  {
    this->Damage = Damage_;
  }

  int UStatusComponentBleed::GetTurnsLeft() const
  {
    return TurnsLeft;
  }

  void UStatusComponentBleed::SetTurnsLeft(int TurnsLeft_)
  {
    this->TurnsLeft = TurnsLeft_;
  }
