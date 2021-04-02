// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InteractableType.generated.h"

UENUM(BlueprintType)
enum class EInteractableType : uint8
{
    IT_None UMETA(DisplayName = "None"),
    IT_Pickup UMETA(DisplayName = "Pickup"),
    IT_Door UMETA(DisplayName = "Door"),
    IT_Trigger UMETA(DisplayName = "Trigger")
};
