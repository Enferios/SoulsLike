
// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "NavigationInvokerComponent.h"

#include "Controller/EnemyController.h"
#include "Controller/EnemyControllerInterface.h"
#include "GameplayMechanics/AIMechanics/BaseProjectile.h"
#include "GameplayMechanics/Stats/CharacterStatsComponent.h"


AEnemyCharacter::AEnemyCharacter()
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AEnemyController::StaticClass();

    WalkSpeed = 400.f;
    RunSpeed = 600.f;

    MeleeDistance = 100.f;
    RangedDistance = 600.f;

    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    GetCharacterMovement()->bOrientRotationToMovement = true;

    SensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComponent"));
    NavigationInvokerComponent = CreateDefaultSubobject<UNavigationInvokerComponent>(TEXT("NavigationInvoker"));
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    SensingComponent->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeePawn);
    CharacterStats->OnCharacterDeath.AddDynamic(this, &AEnemyCharacter::Death);
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

void AEnemyCharacter::SelectAttack_Implementation()
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

void AEnemyCharacter::AttackTrace()
{
    if (CurrentAttackSocket)
    {
        FVector Location = (Cast<USceneComponent>(CurrentAttackSocket))->GetComponentLocation();

        TArray<AActor*> OverlappedActors;

        SpawnAttackOverlapSphere(Location, 100.f, OverlappedActors);

        for (auto& Actor : OverlappedActors)
        {
            if (Actor)
            {
                Actor->TakeDamage(30.f, FDamageEvent(UDamageType::StaticClass()), GetController(), this);
            }
        }

        ActorsToIgnore.Append(OverlappedActors);
    }
    
}

void AEnemyCharacter::SetAttackTraceTimer()
{
    ActorsToIgnore.Add(this);

    GetWorld()->GetTimerManager().SetTimer(AttackTraceTimer, this, &AEnemyCharacter::AttackTrace, 0.02f, true);
}

void AEnemyCharacter::StopAttackTracing()
{
    ActorsToIgnore.Empty();

    GetWorld()->GetTimerManager().ClearTimer(AttackTraceTimer);
}

void AEnemyCharacter::SpawnAttackOverlapSphere(FVector Location, float Radius, TArray<AActor*>& OutOverlappedActors)
{
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
    ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

    UKismetSystemLibrary::SphereOverlapActors(this, Location, Radius, ObjectType, nullptr, ActorsToIgnore, OutOverlappedActors);
}

void AEnemyCharacter::StartAttackTrace_Implementation()
{
    SetAttackTraceTimer();
}

void AEnemyCharacter::StopAttackTrace_Implementation()
{
    StopAttackTracing();
}

bool AEnemyCharacter::SetCurrentAttackSocket(const FName& Tag)
{
    CurrentAttackSocket = Cast<USceneComponent>((GetComponentsByTag(USceneComponent::StaticClass(), Tag))[0]);
    if (CurrentAttackSocket)
        return true;
    else
        return false;

}

float AEnemyCharacter::GetDistanceToTarget()
{
    if (CurrentTarget != nullptr)
    {
        float Distance = FVector::Distance(GetActorLocation(), 
                                    CurrentTarget->GetActorLocation());
        return Distance;
    }

    return 0.f;
}

void AEnemyCharacter::SetCombatMode_Implementation(EAICombatMode NewMode)
{
    CombatMode = NewMode;
    if (CombatMode == EAICombatMode::AICM_Melee)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Melee");
    }
    else
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Ranged");
}

void AEnemyCharacter::SpawnProjectile_Implementation()
{
    if (ProjectileType)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        SpawnParams.Instigator = this;
        GetWorld()->SpawnActor<AActor>(ProjectileType, GetActorTransform(), SpawnParams);
    }
   
}

void AEnemyCharacter::Death()
{
    Super::Death();

    if (DeathMontage)
    {
        Multicast_PlayMontage(GetMesh(), DeathMontage);
    }

    DetachFromControllerPendingDestroy();
    SetLifeSpan(5.f);
}