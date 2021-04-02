// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "CharacterStats.generated.h"

USTRUCT(Blueprintable)
struct FCharacterStats : public FTableRowBase
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsDead;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HealthMax;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HealthCurrent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaMax;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaCurrent;
};