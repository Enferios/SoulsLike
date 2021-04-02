// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterWeaponMode.generated.h"

UENUM(BlueprintType)
enum class ECharacterWeaponMode : uint8
{
    CWM_None UMETA(DisplayName = "None"),
    CWM_Brawl UMETA(DisplayName = "Brawl"),
    CWM_Longsword UMETA(DisplayName = "Longsword")
};
