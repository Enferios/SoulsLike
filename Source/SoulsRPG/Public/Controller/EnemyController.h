// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Controller/EnemyControllerInterface.h"

#include "EnemyController.generated.h"

/**
 * 
 */
class UBehaviorTree;

UCLASS()
class SOULSRPG_API AEnemyController : public AAIController,
	public IEnemyControllerInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Behavior Tree")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI | Combat")
	AActor* CurrentTarget;

public:

	void SetTarget(AActor* NewTarget);
	void SetTarget_Implementation(AActor* NewTarget);

	void ClearTarget();

	void SelectAttack();
	void SelectAttack_Implementation();

protected:

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	void LookAtTarget();
	

};
