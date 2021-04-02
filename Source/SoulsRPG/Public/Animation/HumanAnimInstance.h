// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "DataTypes/CharacterWeaponMode.h"
#include "Animation/HumanAnimInstanceInterface.h"

#include "HumanAnimInstance.generated.h"

/**
 * 
 */

class ASoulsBaseCharacter;

UCLASS()
class SOULSRPG_API UHumanAnimInstance : public UAnimInstance,
	public IHumanAnimInstanceInterface
{
	GENERATED_BODY()

public:

	UHumanAnimInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation | Movement")
	bool bIsFalling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation | Movement")
	bool bIsSprinting;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation | Movement")
	bool bIsRolling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation | Combat")
	ECharacterWeaponMode WeaponMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation | Movement")
	float Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation | Movement")
	float CurrentAcceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation | References")
	ASoulsBaseCharacter* Character;
	
public:

	UFUNCTION(BlueprintCallable, Category = "AnimInstance")
	void UpdateAnimationProperties();

	FORCEINLINE void ToggleSprintMode(bool IsEnabled) { bIsSprinting = IsEnabled; }

	void EnableAttackCollision();
	void EnableAttackCollision_Implementation();

	void DisableAttackCollision();
	void DisableAttackCollision_Implementation();
};
