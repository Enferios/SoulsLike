// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/SoulsPlayerController.h"
#include "Blueprint/UserWidget.h"

#include "HUD/GameOverlay.h"
#include "Character/SoulsPlayerCharacter.h"
#include "GameplayMechanics/Stats/CharacterStatsComponent.h"



void ASoulsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitOverlayWidget();

	ASoulsPlayerCharacter* Char = Cast<ASoulsPlayerCharacter>(GetCharacter());
	if (Char && IsLocalController())
	{
		Char->CharacterStats->OnUpdateHealthPercent.AddDynamic(this, &ASoulsPlayerController::UpdateHealthPercent);
	}
}

void ASoulsPlayerController::InitOverlayWidget()
{
	
	if  (IsLocalController())
	{
		if (GameOverlayClass != nullptr)
		{
			GameOverlayWidget = CreateWidget<UGameOverlay>(this, GameOverlayClass);
		}

		if (GameOverlayWidget != nullptr)
		{
			GameOverlayWidget->AddToViewport();
		}
	}

}

void ASoulsPlayerController::UpdateHealthWidget(float NewPercent)
{
	{
		UpdateHealthPercent(NewPercent);
	}
}


void ASoulsPlayerController::UpdateHealthPercent(float NewPercent)
{
	if (GameOverlayWidget)
	{
		GameOverlayWidget->UpdateHealthPercent(NewPercent);
	}

}



