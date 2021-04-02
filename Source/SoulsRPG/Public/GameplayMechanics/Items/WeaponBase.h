// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayMechanics/Items/Master_Item.h"
#include "WeaponBase.generated.h"

/**
 * 
 */

UCLASS()
class SOULSRPG_API AWeaponBase : public AMaster_Item
{
	GENERATED_BODY()
public:

	AWeaponBase();

protected:

	virtual void ApplyDamage(AActor* Target);

};
