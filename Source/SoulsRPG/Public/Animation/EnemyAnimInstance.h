// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOULSRPG_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, Category = "Animation | Movement")
	float Velocity;

	UPROPERTY(BlueprintReadOnly, Category = "Animation | Reference")
	APawn* PawnOwner;

protected:

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties();
};
