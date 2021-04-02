// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "DataTypes/CharacterStats.h"

#include "CharacterStatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOULSRPG_API UCharacterStatsComponent : public UActorComponent
{
	GENERATED_BODY()

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStatsComponentUpdateHealthPercent, float, NewPercent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);

public:	
	// Sets default values for this component's properties
	UCharacterStatsComponent();

	UPROPERTY(ReplicatedUsing = OnRep_UpdateStats, EditAnywhere, BlueprintReadWrite)
	FCharacterStats Stats;

	UPROPERTY(BlueprintAssignable)
	FStatsComponentUpdateHealthPercent OnUpdateHealthPercent;

	UPROPERTY(BlueprintAssignable)
	FDeathDelegate OnCharacterDeath;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ChangeHealth(float Amount, bool IsCurrent = true);

	UFUNCTION()
	void Death();

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_UpdateStats();

private:

	UFUNCTION(Client, Reliable)
	void UpdateHealth();
	
		
};
