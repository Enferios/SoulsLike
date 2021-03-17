// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SoulsBaseCharacter.h"
#include "SoulsPlayerCharacter.generated.h"

/**
 * 
 */

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SOULSRPG_API ASoulsPlayerCharacter : public ASoulsBaseCharacter
{
	GENERATED_BODY()

public:

	ASoulsPlayerCharacter();

	float TurnRate;
	float LookUpRate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* FollowCamera;


public:
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	/** Uses for rotate spring arm around character */
	void LookUp(float AxisValue);

	/** Uses for rotate spring arm around character */
	void Turn(float AxisValue);
};
