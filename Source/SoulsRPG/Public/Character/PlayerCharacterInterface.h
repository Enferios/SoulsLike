// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "GameplayMechanics/Pickups/InteractableInfo.h"
#include "DataTypes/ItemInfo.h"

#include "PlayerCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SOULSRPG_API IPlayerCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetNameplateVisibility(bool NewVisibility);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateNameplateInfo(const FInteractableInfo& NewInfo);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EquipItem(const FItemInfo& Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EnableAttackCollision();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DisableAttackCollision();
};
