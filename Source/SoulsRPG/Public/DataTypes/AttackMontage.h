// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "AttackMontage.generated.h"

class UAnimMontage;

USTRUCT(Blueprintable)
struct FAttackMontage : public FTableRowBase
{
    GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UAnimMontage* Montage;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FName Tag;
};