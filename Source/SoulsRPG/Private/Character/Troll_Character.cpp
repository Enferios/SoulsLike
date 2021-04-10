// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Troll_Character.h"

#include "Components/SceneComponent.h"

ATroll_Character::ATroll_Character()
{
    LightAttackLeftSocket = CreateDefaultSubobject<USceneComponent>(TEXT("LightAttackLeftSocket"));
    LightAttackLeftSocket->SetupAttachment(GetMesh(), "b_MF_Weapon_L");
    LightAttackLeftSocket->ComponentTags.Add("LeftHand");

    HeavyAttackRightSocket = CreateDefaultSubobject<USceneComponent>(TEXT("HeavyAttackRightSocket"));
    HeavyAttackRightSocket->SetupAttachment(GetMesh(), "b_MF_Weapon_R");
    HeavyAttackRightSocket->ComponentTags.Add("RightHandWeapon");

    RangedAttackSocket = CreateDefaultSubobject<USceneComponent>(TEXT("RangedAttackSocket"));
    RangedAttackSocket->SetupAttachment(GetMesh(), "b_MF_Head");
    RangedAttackSocket->ComponentTags.Add("RangedWeapon");
}

void ATroll_Character::SelectAttack_Implementation()
{
    switch (CombatMode)
    {
    case EAICombatMode::AICM_Melee:
        if (CheckPercentChance(25.f))
             HeavyAttack();
        else
            LightAttack();
        break;
    case EAICombatMode::AICM_Ranged:
        RangedAttack();
        break;
    default:
        break;
    }
}

void ATroll_Character::LightAttack()
{
    auto RandomMontage = GetRandomMontage(LightAttackMontages);

    if (RandomMontage.Montage != nullptr)
    {
        bool bIsValidSocket = SetCurrentAttackSocket(RandomMontage.Tag);
        if (bIsValidSocket)
        {
            Multicast_PlayMontage(GetMesh(), RandomMontage.Montage);
        }
    }
   
}

void ATroll_Character::HeavyAttack()
{
    auto RandomMontage = GetRandomMontage(HeavyAttackMontages);
    if (RandomMontage.Montage != nullptr)
    {
        bool bIsValidSocket = SetCurrentAttackSocket(RandomMontage.Tag);
        if (bIsValidSocket)
        {
            Multicast_PlayMontage(GetMesh(), RandomMontage.Montage);
        }
    }
   
}

void ATroll_Character::RangedAttack()
{
    auto RandomMontage = GetRandomMontage(RangedAttackMontages);
    if (RandomMontage.Montage != nullptr)
    {
        bool bIsValidSocket = SetCurrentAttackSocket(RandomMontage.Tag);
        if (bIsValidSocket)
        {
            Multicast_PlayMontage(GetMesh(), RandomMontage.Montage);
        }
    }
}