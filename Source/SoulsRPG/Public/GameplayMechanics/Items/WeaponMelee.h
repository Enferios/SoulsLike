// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayMechanics/Items/WeaponBase.h"
#include "WeaponMelee.generated.h"

/**
 * 
 */

class USceneComponent;

UCLASS()
class SOULSRPG_API AWeaponMelee : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AWeaponMelee();

private:

	bool bIsTracingEnabled;

	/** Delay in seconds before the combo counter will be cleared */
	float ComboCounterClearDelay;

	/** Interval between CombatCollisionTrace() calls */
	float TraceInterval;
	int32 PointsCount;

	int32 CurrentCombo;


	USceneComponent* TraceStartSocket;
	USceneComponent* TraceEndSocket;

	/** Contains actors, already hitted in current attack, clears after the attack is ended */
	TArray<AActor*> AlreadyHittedActors;
	TArray<FVector> Points;
	TArray<FVector> PointsOld;

	FTimerHandle AttackTraceTimer;
	FTimerHandle ComboTimer;

public:

	UFUNCTION()
	virtual void CombatCollisionTrace();
	void TraceForTargets();

	void SetPoints();
	void InitPoints();

	void PlayAttackSound_Implementation() override;

	void Attack(bool IsHeavyAttack);
	virtual void Attack_Implementation(bool IsHeavyAttack);

	

protected:

	void BeginPlay() override;

	void Server_TryEnableCombatTracing() override;
	void Server_TryDisableCombatTracing() override;

	void ApplyDamage(AActor* Target) override;
	void ClearHittedActors();

private:

	void IncrementComboCounter();
	void ClearComboCounter();
};
