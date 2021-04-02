// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "CharacterEquippedItems.generated.h"

class AMaster_Item;

USTRUCT(Blueprintable)
struct FCharacterEquippedItems : public FTableRowBase
{
    GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AMaster_Item* MainWeapon;
};