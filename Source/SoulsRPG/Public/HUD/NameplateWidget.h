// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUD/NameplateWidgetInterface.h"
#include "NameplateWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOULSRPG_API UNameplateWidget : public UUserWidget,
	public INameplateWidgetInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Nameplate")
	FText DisplayName;
	
public:

	void SetName(const FText& NewName);
	void SetNameplateVisibility(bool IsVisible);
};
