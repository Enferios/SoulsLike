// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "SoulsBaseCharacter.generated.h"

class UHumanAnimInstance;
class USceneComponent;
class UCharacterStatsComponent;
class UAnimMontage;

UCLASS()
class SOULSRPG_API ASoulsBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASoulsBaseCharacter();

	bool bIsAttacking;

	UPROPERTY(BlueprintReadOnly)
	bool bIsHeavyAttackCharged;

	UPROPERTY(ReplicatedUsing = OnRep_bIsRolling)
	bool bIsRolling;

	UPROPERTY(ReplicatedUsing = OnRep_bIsSprinting)
	bool bIsSprinting;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	UHumanAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	USceneComponent* TwoHandedWeaponEquipSocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	USceneComponent* TwoHandedWeaponHandSocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	UCharacterStatsComponent* CharacterStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
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

};
