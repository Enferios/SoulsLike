// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FootStepSoundNotify.generated.h"

/**
 * 
 */
UCLASS()
class SOULSRPG_API UFootStepSoundNotify : public UAnimNotify
{
	GENERATED_BODY()

public:

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
