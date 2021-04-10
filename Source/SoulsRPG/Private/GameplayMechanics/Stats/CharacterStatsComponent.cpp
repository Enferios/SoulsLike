// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayMechanics/Stats/CharacterStatsComponent.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UCharacterStatsComponent::UCharacterStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicated(true);

	Stats.HealthMax = 100.f;
	Stats.HealthCurrent = Stats.HealthMax;

	// ...
}

void UCharacterStatsComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCharacterStatsComponent, Stats);
}


// Called when the game starts
void UCharacterStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UCharacterStatsComponent::TakeDamage);

	UpdateHealth();

	// ...
	
}


// Called every frame
void UCharacterStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterStatsComponent::ChangeHealth(float Amount, bool IsCurrent)
{
	if (IsCurrent)
	{
		Stats.HealthCurrent -= Amount;
		if (Stats.HealthCurrent <= 0.f)
		{
			Stats.HealthCurrent = 0.f;
			Death();
		}
	}
	else
	{
		Stats.HealthMax -= Amount;
		if (Stats.HealthMax < 0.f)
			Stats.HealthMax = 0;
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString().SanitizeFloat(Stats.HealthCurrent));
}

void UCharacterStatsComponent::Death()
{
	Stats.bIsDead = true;
	OnCharacterDeath.Broadcast();
}


void UCharacterStatsComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Stats.bIsDead)
		return;

	ChangeHealth(Damage);
}

void UCharacterStatsComponent::UpdateHealth_Implementation()
{
	float HealthPercent = Stats.HealthCurrent / Stats.HealthMax;
	OnUpdateHealthPercent.Broadcast(HealthPercent);
}

void UCharacterStatsComponent::OnRep_UpdateStats()
{
	UpdateHealth();
}
