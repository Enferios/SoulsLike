// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SOULSRPG_API IEnemyControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy Controller Interface")
	void SetTarget(AActor* NewTarget);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy Controller Interface")
	void SelectAttack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy Controller Interface")
	void ClearTarget();

};
