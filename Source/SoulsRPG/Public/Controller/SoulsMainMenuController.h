// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SoulsMainMenuController.generated.h"

/**
 * 
 */
class UMainMenuOverlayWidget;

UCLASS()
class SOULSRPG_API ASoulsMainMenuController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<UMainMenuOverlayWidget> OverlayWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
	UMainMenuOverlayWidget* OverlayWidget;
	
protected:

	void BeginPlay() override;

	void InitOverlayWidget();
};
