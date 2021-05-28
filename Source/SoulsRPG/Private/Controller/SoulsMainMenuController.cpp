// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/SoulsMainMenuController.h"

#include "HUD/MainMenuOverlayWidget.h"

void ASoulsMainMenuController::BeginPlay()
{
    if (IsLocalController())
    {
        SetShowMouseCursor(true);
        SetInputMode(FInputModeUIOnly::FInputModeUIOnly());
        InitOverlayWidget();
    }
}

void ASoulsMainMenuController::InitOverlayWidget()
{
    if (OverlayWidgetClass != nullptr)
    {
        OverlayWidget = CreateWidget<UMainMenuOverlayWidget>(this, OverlayWidgetClass);
        if (OverlayWidget)
            OverlayWidget->AddToViewport();
    }
}