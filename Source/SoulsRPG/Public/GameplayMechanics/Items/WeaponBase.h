// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayMechanics/Items/Master_Item.h"

#include "GameplayMechanics/Items/WeaponInterface.h"

#include "WeaponBase.generated.h"

/**
 * 
 */

UCLASS()
class SOULSRPG_API AWeaponBase : public AMaster_Item,
	public IWeaponInterface
{
	GENERATED_BODY()
public:

	AWeaponBase();

public:

	void PlayAttackMontage();
	virtual void PlayAttackSound_Implementation();

	template <class T> T* GetRandomFromArray(const TArray<T*>& Array);

protected:

	virtual void ApplyDamage(AActor* Target);

	

};

template <class T> T* AWeaponBase::GetRandomFromArray(const TArray<T*>& Array)
{
	if (Array.Num() > 0)
	{
		int32 MaxIndex = Array.Num() - 1;

		int32 RandomIndex = FMath::RandRange(0, MaxIndex);

		return Array[RandomIndex];
	}

	else return nullptr;
}
