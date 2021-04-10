// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EnemyCharacter.h"
#include "Troll_Character.generated.h"

/**
 * 
 */

class USceneComponent;

UCLASS()
class SOULSRPG_API ATroll_Character : public AEnemyCharacter
{
	GENERATED_BODY()

public:

	ATroll_Character();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI | Combat")
	USceneComponent* LightAttackLeftSocket;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI | Combat")
	USceneComponent* HeavyAttackRightSocket;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI | Combat")
	USceneComponent* RangedAttackSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Animation")
	TArray<FAttackMontage> LightAttackMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Animation")
	TArray<FAttackMontage> HeavyAttackMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Animation")
	TArray<FAttackMontage> RangedAttackMontages;
	
public:

	void SelectAttack_Implementation() override;

	void LightAttack();
	void HeavyAttack();
	void RangedAttack();
};
