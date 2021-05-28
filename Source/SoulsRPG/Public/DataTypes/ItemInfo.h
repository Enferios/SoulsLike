// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "DataTypes/ItemType.h"
#include "DataTypes/WeaponStats.h"

#include "ItemInfo.generated.h"

class AMaster_Item;
USTRUCT(Blueprintable)
struct FItemInfo : public FTableRowBase
{
    GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemType Type;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AMaster_Item> ItemClass;
   
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FWeaponStats WeaponStats;
};