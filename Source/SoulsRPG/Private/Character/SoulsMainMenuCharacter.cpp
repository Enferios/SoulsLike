// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SoulsMainMenuCharacter.h"

// Sets default values
ASoulsMainMenuCharacter::ASoulsMainMenuCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoulsMainMenuCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoulsMainMenuCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASoulsMainMenuCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

