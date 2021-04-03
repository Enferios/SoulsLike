// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SoulsBaseCharacter.h"

#include "Character/PlayerCharacterInterface.h"
#include "DataTypes/CharacterEquippedItems.h"
#include "DataTypes/CharacterWeaponMode.h"

#include "SoulsPlayerCharacter.generated.h"

/**
 * 
 */

class USpringArmComponent;
class UCameraComponent;
class ASoulsPlayerController;
class UInteractionComponent;

UCLASS()
class SOULSRPG_API ASoulsPlayerCharacter : public ASoulsBaseCharacter,
	public IPlayerCharacterInterface
{
	GENERATED_BODY()

public:

	ASoulsPlayerCharacter();

	bool bMovementEnabled;
	bool bInputEnabled;

	UPROPERTY(ReplicatedUsing = OnRep_IsMoving, BlueprintReadOnly)
	bool bIsMoving;

	UPROPERTY(ReplicatedUsing = OnRep_WeaponMode, VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	ECharacterWeaponMode WeaponMode;

	float TurnRate;
	float LookUpRate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* PickupMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* RollingMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* AttackChargingMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* AttackLightMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* AttackHeavyMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* WeaponDrawMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	ASoulsPlayerController* PlayerController;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedItems, VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	FCharacterEquippedItems EquippedItems;


public:

	void BeginPlay() override;

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;


	void ShiftKeyPressed();
	void ShiftKeyReleased();

	void SpacebarKeyPressed();
	void FKeyPressed();

	void DrawMainWeaponPressed();

	void LMBDown();
	void LMBUp();

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	/** Uses for rotate spring arm around character */
	void LookUp(float AxisValue);

	/** Uses for rotate spring arm around character */
	void Turn(float AxisValue);

	bool CanMove();

	UFUNCTION(Server, Reliable)
	void Server_ActivateSprintMode();

	UFUNCTION(Server, Reliable)
	void Server_DeactivateSprintMode();

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_SetWalkSpeed(float NewSpeed);

	UFUNCTION(Server, Reliable)
	void Server_TryRolling();

	
	UFUNCTION(Server, Reliable)
	void Server_TryChargeAttack();

	UFUNCTION(Server, Reliable)
	void Server_TryAttack();

	UFUNCTION(Client, Reliable)
	void Client_SetNameplateVisibility(bool NewVisibility);

	UFUNCTION(Client, Reliable)
	void Client_SetNameplateNameText(const FText& NewText);

	UFUNCTION(Server, Reliable)
	void Server_TryInteract();

	UFUNCTION()
	void OnRep_EquippedItems();

	void EquipItem(const FItemInfo& Item);
	virtual void EquipItem_Implementation(const FItemInfo& Item);

	UFUNCTION()
	void OnRep_WeaponMode();

	UFUNCTION(Server, Reliable)
	void Server_TryDrawWeapon();

	UFUNCTION(Server, Reliable)
	void Server_TrySheathWeapon();

	void EnableAttackCollision();
	void EnableAttackCollision_Implementation();

	void DisableAttackCollision();
	void DisableAttackCollision_Implementation();

	void Death() override;

	UFUNCTION()
	void OnRep_IsMoving();

	UFUNCTION(Server, Reliable)
	void Server_CheckIsMoving();

	void EquipWeaponNotify();
	void EquipWeaponNotify_Implementation();

	void UnequipWeaponNotify();
	void UnequipWeaponNotify_Implementation();
	
	UFUNCTION(Server, Reliable)
	void Server_TrySetWeaponMode(ECharacterWeaponMode NewMode);
};
