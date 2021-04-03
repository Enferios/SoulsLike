// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SoulsBaseCharacter.h"

#include "Character/EnemyCharacterInterface.h"

#include "EnemyCharacter.generated.h"

/**
 * 
 */

class UPawnSensingComponent;

UCLASS()
class SOULSRPG_API AEnemyCharacter : public ASoulsBaseCharacter,
	public IEnemyCharacterInterface
{
	GENERATED_BODY()

public:

	AEnemyCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Movement")
	float WalkSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Movement")
	float RunSpeed;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Sensing")
	UPawnSensingComponent* SensingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Combat")
	AActor* CurrentTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Animation")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Animation")
	UAnimMontage* TauntMontage;

	void ClearTarget();
	void ClearTarget_Implementation();

	UFUNCTION()
	void OnSeePawn(APawn* Pawn);

	void SetTarget(AActor* NewTarget);

	void Attack();
	void Attack_Implementation();

	void Taunt();
	void Taunt_Implementation();

protected:

	void BeginPlay() override;




};
