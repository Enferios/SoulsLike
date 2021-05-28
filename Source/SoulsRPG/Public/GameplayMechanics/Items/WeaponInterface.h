// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInterface.generated.h"

class USoundCue;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SOULSRPG_API IWeaponInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon Interface")
	void PlayAttackSound();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon Interface")
	void Attack(bool IsHeavyAttack);

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
