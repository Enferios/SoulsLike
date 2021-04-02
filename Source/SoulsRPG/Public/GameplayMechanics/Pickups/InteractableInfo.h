// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "DataTypes/InteractableType.h"
#include "InteractableInfo.generated.h"

/**
 * 
 */

USTRUCT(Blueprintable)
struct FInteractableInfo : public FTableRowBase
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EInteractableType Type;

};