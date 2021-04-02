// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerBars.generated.h"

/**
 * 
 */
UCLASS()
class SOULSRPG_API UPlayerBars : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateHealth(float NewPercent);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateStamina(float NewPercent);

};
