// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "DataTypes/AttackMontage.h"
#include "Character/BaseCharacterInterface.h"

#include "SoulsBaseCharacter.generated.h"

class UHumanAnimInstance;
class USceneComponent;
class UCharacterStatsComponent;
class UAnimMontage;

UCLASS()
class SOULSRPG_API ASoulsBaseCharacter : public ACharacter,
	public IBaseCharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASoulsBaseCharacter();

	bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	bool bIsDead;

	UPROPERTY(BlueprintReadOnly)
	bool bIsHeavyAttackCharged;

	UPROPERTY(ReplicatedUsing = OnRep_bIsRolling)
	bool bIsRolling;

	UPROPERTY(ReplicatedUsing = OnRep_bIsSprinting)
	bool bIsSprinting;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Animation")
	UHumanAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Equipment")
	USceneComponent* TwoHandedWeaponEquipSocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Equipment")
	USceneComponent* TwoHandedWeaponHandSocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Stats")
	UCharacterStatsComponent* CharacterStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Animation")
	UAnimMontage* DeathMontage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void Server_PlayMontage(UAnimMontage* Montage);
	void Server_PlayMontage_Implementation(UAnimMontage* Montage);

	/** Uses for playing animation montages on all clients */
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void Multicast_PlayMontage(USkeletalMeshComponent* MeshToPlay, UAnimMontage* Montage,
										FName Section = "None");

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Character | Combat")
	void Server_SetIsAttackCharged(bool IsCharged);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Character | Combat")
	void Server_AttackEnd();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Character | Combat")
	void Server_RollEnd();

	UFUNCTION()
	void OnRep_bIsSprinting();

	UFUNCTION()
	void OnRep_bIsRolling();

	UFUNCTION()
	virtual void Death();

	bool CheckIsDead();
	bool CheckIsDead_Implementation();

	/** Calls when character mesh make step in animation */
	void FootstepNotify();
	virtual void FootstepNotify_Implementation();

	/** Calls when character gets hit */
	UFUNCTION()
		virtual void PlayHitMontage();

	void OnTakeDamage(AActor* DamagedActor, float Damage,
	const class UDamageType* DamageType, class AController* InstigatedBy,
	AActor* DamageCauser);

protected:

	UFUNCTION()
	virtual FAttackMontage GetRandomMontage(TArray<FAttackMontage> Montages);

	bool CheckPercentChance(float SuccessPercent);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void Multicast_SetupDeathCollision();




};
