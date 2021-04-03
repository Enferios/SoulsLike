// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyAnimInstance.h"

void UEnemyAnimInstance::UpdateAnimationProperties()
{
    PawnOwner = TryGetPawnOwner();
	if (PawnOwner)
	{
		Velocity = PawnOwner->GetVelocity().Size();
	}
}