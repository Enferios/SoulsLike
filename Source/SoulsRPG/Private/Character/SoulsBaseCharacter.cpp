// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SoulsBaseCharacter.h"

#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
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

	bIsDead = false;
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

void ASoulsBaseCharacter::Server_PlayMontage_Implementation(UAnimMontage* Montage)
{
	Multicast_PlayMontage(GetMesh(), Montage);
}

// TODO make mesh implemented inside the function instead
void ASoulsBaseCharacter::Multicast_PlayMontage_Implementation(USkeletalMeshComponent* MeshToPlay,
										UAnimMontage* Montage, FName Section)
{
	if (MeshToPlay == nullptr || Montage == nullptr)
		return;

	MeshToPlay->GetAnimInstance()->Montage_Play(Montage);
	if (Section != "None")
	{
		MeshToPlay->GetAnimInstance()->Montage_JumpToSection(Section);
	}
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
	bIsDead = true;

	Multicast_SetupDeathCollision();
}

bool ASoulsBaseCharacter::CheckIsDead_Implementation()
{
	return bIsDead;
}

FAttackMontage ASoulsBaseCharacter::GetRandomMontage(TArray<FAttackMontage> Montages)
{
	if (Montages.Num() <= 0)
		return FAttackMontage();

	int32 MaxRange = Montages.Num() - 1;
	int32 MontageIndex = FMath::RandRange(0, MaxRange);

	if (Montages[MontageIndex].Montage != nullptr)
		return Montages[MontageIndex];
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BaseCharacter->GetRandomMontage() : montage is not valid!"));
	}

	return FAttackMontage();
}

bool ASoulsBaseCharacter::CheckPercentChance(float SuccessPercent)
{
	if (SuccessPercent == 0.f)
		return false;

	float RandomPercent = FMath::RandRange(0.f, 100.f);
	if (RandomPercent <= SuccessPercent)
		return true;

	else
		return false;
}

void ASoulsBaseCharacter::Multicast_SetupDeathCollision_Implementation()
{
	GetCapsuleComponent()->SetCollisionProfileName("Ragdoll");
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

void ASoulsBaseCharacter::FootstepNotify_Implementation()
{

}

void ASoulsBaseCharacter::PlayHitMontage()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Hit!");
}

void ASoulsBaseCharacter::OnTakeDamage(AActor* DamagedActor, float Damage,
	const class UDamageType* DamageType, class AController* InstigatedBy,
	AActor* DamageCauser)
{

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Hit!");

	PlayHitMontage();
}