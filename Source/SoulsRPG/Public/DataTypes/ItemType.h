// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemType.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    IT_None UMETA(DisplayName = "None"),
    IT_Weapon UMETA(DisplayName = "Weapon")
};
