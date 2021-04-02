// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayMechanics/Items/WeaponBase.h"
#include "WeaponMelee.generated.h"

/**
 * 
 */

class USceneComponent;
class AActor;

UCLASS()
class SOULSRPG_API AWeaponMelee : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AWeaponMelee();

private:

	bool bIsTracingEnabled;

	/** Interval between CombatCollisionTrace() calls */
	float TraceInterval;
	int32 PointsCount;


	USceneComponent* TraceStartSocket;
	USceneComponent* TraceEndSocket;

	/** Contains actors, already hitted in current attack, clears after the attack is ended */
	TArray<AActor*> AlreadyHittedActors;
	TArray<FVector> Points;
	TArray<FVector> PointsOld;

	FTimerHandle AttackTraceTimer;

public:

	UFUNCTION()
	virtual void CombatCollisionTrace();
	void TraceForTargets();

	void SetPoints();
	void InitPoints();


protected:

	void BeginPlay() override;

	void Server_TryEnableCombatTracing() override;
	void Server_TryDisableCombatTracing() override;

	void ApplyDamage(AActor* Target) override;
	void ClearHittedActors();
};
