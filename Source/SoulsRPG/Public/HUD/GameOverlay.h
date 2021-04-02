// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "GameplayMechanics/Pickups/InteractableInfo.h"

#include "GameOverlay.generated.h"

/**
 * 
 */


struct FInteractableInfo;

UCLASS()
class SOULSRPG_API UGameOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Overlay | Interaction")
	FInteractableInfo NameplateInfo;

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetNameplateVisibility(bool IsVisible);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetNameplateNameText(const FText& NewText);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthPercent(float NewPercent);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateStaminaPercent(float NewPercent);

};
