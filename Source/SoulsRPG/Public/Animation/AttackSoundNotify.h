// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AttackSoundNotify.generated.h"

/**
 * 
 */
UCLASS()
class SOULSRPG_API UAttackSoundNotify : public UAnimNotify
{
	GENERATED_BODY()

public:

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animtaion) override;
	
};
