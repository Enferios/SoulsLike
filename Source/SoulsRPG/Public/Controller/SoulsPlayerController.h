// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"


#include "SoulsPlayerController.generated.h"

/**
 * 
 */


class UGameOverlay;

UCLASS()
class SOULSRPG_API ASoulsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<UGameOverlay> GameOverlayClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	UGameOverlay* GameOverlayWidget;

public:

	UFUNCTION(BlueprintCallable)
	void UpdateHealthPercent(float NewPercent);

	UFUNCTION()
	void UpdateHealthWidget(float NewPercent);

protected:

	void BeginPlay();

private:

	void InitOverlayWidget();

};
