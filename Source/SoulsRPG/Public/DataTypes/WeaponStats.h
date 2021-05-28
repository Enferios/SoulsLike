// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "WeaponStats.generated.h"

class UAnimMontage;
class USoundCue;

USTRUCT(Blueprintable)
struct FWeaponStats : public FTableRowBase
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageMin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageMax;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PowerAttackDamageMult;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CritChanceMult;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CritDamageMult;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaDrain;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaDrainPowerAttack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UAnimMontage*> BasicAttacks;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UAnimMontage*> PowerAttacks;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UAnimMontage*> BlockingMontages;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UAnimMontage*> HitMontages;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<USoundCue*> AttackSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<USoundCue*> BlockAndHitSounds;

};
