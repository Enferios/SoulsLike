// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BaseCharacterInterface.generated.h"

class UAnimMontage;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBaseCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SOULSRPG_API IBaseCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BaseCharacterInterface")
	bool CheckIsDead();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BaseCharacterInterface")
	void FootstepNotify();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BaseCharacterInterface")
	void Server_PlayMontage(UAnimMontage* Montage);
};
