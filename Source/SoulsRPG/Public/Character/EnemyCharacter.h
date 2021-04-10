// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SoulsBaseCharacter.h"

#include "Character/EnemyCharacterInterface.h"
#include "DataTypes/AttackMontage.h"
#include "DataTypes/AICombatMode.h"

#include "EnemyCharacter.generated.h"

/**
 * 
 */

class UPawnSensingComponent;
class USceneComponent;
class ABaseProjectile;
class UNavigationInvokerComponent;

UCLASS()
class SOULSRPG_API AEnemyCharacter : public ASoulsBaseCharacter,
	public IEnemyCharacterInterface
{
	GENERATED_BODY()

public:

	AEnemyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI | Combat")
	EAICombatMode CombatMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Movement")
	float WalkSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Movement")
	float RunSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Combat")
	float MeleeDistance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Combat")
	float RangedDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Combat")
	float LightAttackDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Combat")
	float HeavyAttackDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Combat")
	float RangedAttackDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Sensing")
	UPawnSensingComponent* SensingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Navigation")
	UNavigationInvokerComponent* NavigationInvokerComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Combat")
	AActor* CurrentTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Combat")
	TSubclassOf<ABaseProjectile> ProjectileType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Animation")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Animation")
	UAnimMontage* TauntMontage;

private:

	UActorComponent* CurrentAttackSocket;

	FTimerHandle AttackTraceTimer;

	TArray<AActor*> ActorsToIgnore;


public:

	void ClearTarget();
	void ClearTarget_Implementation();

	UFUNCTION()
		void OnSeePawn(APawn* Pawn);

	void SetTarget(AActor* NewTarget);

	void SelectAttack();
	virtual void SelectAttack_Implementation();

	void Taunt();
	void Taunt_Implementation();

protected:

	void BeginPlay() override;

	void AttackTrace();

	void SetAttackTraceTimer();
	void StopAttackTracing();

	void StartAttackTrace();
	void StartAttackTrace_Implementation();

	void StopAttackTrace();
	void StopAttackTrace_Implementation();

	void SpawnAttackOverlapSphere(FVector Location, float Radius, TArray<AActor*>& OutOverlappedActors);

	void Death() override;

	FORCEINLINE UActorComponent* GetCurrentAttackSocket() const {return CurrentAttackSocket;}

	/** Return true if Socket is valid */
	bool SetCurrentAttackSocket(const FName& Tag);

	float GetDistanceToTarget();

	void SetCombatMode(EAICombatMode NewMode);
	void SetCombatMode_Implementation(EAICombatMode NewMode);

	void SpawnProjectile();
	virtual void SpawnProjectile_Implementation();
};
