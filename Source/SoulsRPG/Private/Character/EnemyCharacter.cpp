// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

#include "Controller/EnemyController.h"
#include "Controller/EnemyControllerInterface.h"


AEnemyCharacter::AEnemyCharacter()
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AEnemyController::StaticClass();

    WalkSpeed = 400.f;
    RunSpeed = 600.f;

    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    GetCharacterMovement()->bOrientRotationToMovement = true;

    SensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComponent"));
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    SensingComponent->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeePawn);
}

void AEnemyCharacter::OnSeePawn(APawn* Pawn)
{
    if (Pawn && CurrentTarget == nullptr)
    {
        SetTarget(Pawn);
        IEnemyControllerInterface::Execute_SetTarget(GetController(), Pawn);
    }
}

void AEnemyCharacter::SetTarget(AActor* NewTarget)
{

    CurrentTarget = NewTarget;
}

void AEnemyCharacter::ClearTarget_Implementation()
{
    CurrentTarget = nullptr;
}

void AEnemyCharacter::Attack_Implementation()
{
    if (AttackMontage)
    {
        Multicast_PlayMontage(GetMesh(), AttackMontage);
    }
}

void AEnemyCharacter::Taunt_Implementation()
{
    Multicast_PlayMontage(GetMesh(), TauntMontage);
}