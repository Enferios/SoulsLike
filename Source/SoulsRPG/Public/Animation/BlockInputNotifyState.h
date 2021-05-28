// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "BlockInputNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class SOULSRPG_API UBlockInputNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:

public:

	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float Duration) override;
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
