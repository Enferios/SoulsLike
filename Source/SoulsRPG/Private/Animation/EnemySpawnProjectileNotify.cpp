// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemySpawnProjectileNotify.h"

#include "Character/EnemyCharacterInterface.h"

void UEnemySpawnProjectileNotify::Notify(USkeletalMeshComponent* MeshComp,
        UAnimSequenceBase* Animation)
{
	AActor* OwnerPawn = MeshComp->GetOwner();

	if (OwnerPawn->Implements<UEnemyCharacterInterface>())
	{
		IEnemyCharacterInterface::Execute_SpawnProjectile(OwnerPawn);
	}
}