// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SoulsBaseCharacter.h"

#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"

#include "Animation/HumanAnimInstance.h"
#include "GameplayMechanics/Stats/CharacterStatsComponent.h"

// Sets default values
ASoulsBaseCharacter::ASoulsBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	TwoHandedWeaponEquipSocket = CreateDefaultSubobject<USceneComponent>(TEXT("TwoHandedEquipSocket"));
	TwoHandedWeaponEquipSocket->SetupAttachment(GetMesh(), "RShoulderEquipSocket");

	TwoHandedWeaponHandSocket = CreateDefaultSubobject<USceneComponent>(TEXT("TwoHandedHandSocket"));
	TwoHandedWeaponHandSocket->SetupAttachment(GetMesh(), "RHandSocket");

	CharacterStats = CreateDefaultSubobject<UCharacterStatsComponent>(TEXT("CharacterStats"));
}

// Called when the game starts or when spawned
void ASoulsBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AnimInstance = Cast<UHumanAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void ASoulsBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASoulsBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASoulsBaseCharacter::GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(ASoulsBaseCharacter, bIsSprinting);
	DOREPLIFETIME(ASoulsBaseCharacter, bIsRolling);
}

void ASoulsBaseCharacter::Server_SetIsAttackCharged_Implementation(bool IsCharged)
{
	bIsHeavyAttackCharged = IsCharged;
}

void ASoulsBaseCharacter::Server_AttackEnd_Implementation()
{
	bIsHeavyAttackCharged = false;
	bIsAttacking = false;
}


void ASoulsBaseCharacter::Server_RollEnd_Implementation()
{
	bIsRolling = false;
}

void ASoulsBaseCharacter::OnRep_bIsSprinting()
{
	if (AnimInstance != nullptr)
	{
		AnimInstance->ToggleSprintMode(bIsSprinting);
	}
}

void ASoulsBaseCharacter::OnRep_bIsRolling()
{
	if (AnimInstance != nullptr)
	{
		AnimInstance->bIsRolling = bIsRolling;
	}
}

void ASoulsBaseCharacter::Death()
{
}



