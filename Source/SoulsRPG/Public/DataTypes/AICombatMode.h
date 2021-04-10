// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AICombatMode.generated.h"

UENUM(BlueprintType)
enum class EAICombatMode : uint8
{
    AICM_Melee UMETA(DisplayName = "Melee"),
    AICM_Ranged UMETA(DisplayName = "Ranged")
};
