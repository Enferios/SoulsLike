// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayMechanics/Items/WeaponMelee.h"

#include "Components/SceneComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Engine/World.h"
#include "TimerManager.h"


#include "Character/SoulsBaseCharacter.h"
#include "Character/BaseCharacterInterface.h"
#include "DataTypes/WeaponStats.h"
AWeaponMelee::AWeaponMelee()
{
    CurrentCombo = 0;
    ComboCounterClearDelay = 2.f;

    bIsTracingEnabled = false;
    TraceInterval = 0.01;
    PointsCount = 10;
    Points.Init(FVector(0.f), PointsCount);
    PointsOld.Init(FVector(0.f), PointsCount);

    TraceStartSocket = CreateDefaultSubobject<USceneComponent>(TEXT("TraceStartSocket"));
    TraceStartSocket->SetupAttachment(ItemMesh, "TraceStartSocket");
    TraceEndSocket = CreateDefaultSubobject<USceneComponent>(TEXT("TraceEndSocket"));
    TraceEndSocket->SetupAttachment(ItemMesh, "TraceEndSocket");
}

void AWeaponMelee::BeginPlay()
{
    Super::BeginPlay();
}


void AWeaponMelee::InitPoints()
{
    FVector Start = TraceStartSocket->GetComponentLocation();
    FVector End = TraceEndSocket->GetComponentLocation();

    for (int32 i = 0; i < PointsCount; ++i)
    {
        float Alpha = i / PointsCount;
        PointsOld[i] = FMath::Lerp(Start, End, Alpha);
    }
}

void AWeaponMelee::CombatCollisionTrace()
{
    TArray < TEnumAsByte<EObjectTypeQuery>> ObjectType;
    ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
    FHitResult OutHit;

    for (int i = 0; i < PointsCount; ++i)
    {
        FVector Start = PointsOld[i];
        FVector End = Points[i];

        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActors(AlreadyHittedActors);

        GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility, CollisionParams);

        if (OutHit.bBlockingHit)
        {
            ApplyDamage(OutHit.GetActor());
            AlreadyHittedActors.Add(OutHit.GetActor());
        }
    }
    PointsOld = Points;
}

void AWeaponMelee::TraceForTargets()
{
    FVector Start = TraceStartSocket->GetComponentLocation();
    FVector End = TraceEndSocket->GetComponentLocation();

        for (int32 i = 0; i < PointsCount; ++i)
        {
            float Alpha = (float)i / PointsCount;
            Points[i] = FMath::Lerp(Start, End, Alpha);
        }
        
    CombatCollisionTrace();
}

void AWeaponMelee::Server_TryEnableCombatTracing()
{
    bIsTracingEnabled = true;
    AlreadyHittedActors.Add(ItemOwner);
    InitPoints();

    GetWorld()->GetTimerManager().SetTimer(AttackTraceTimer, this, &AWeaponMelee::TraceForTargets, TraceInterval, true);
}

void AWeaponMelee::Server_TryDisableCombatTracing()
{
    bIsTracingEnabled = false;
    GetWorld()->GetTimerManager().ClearTimer(AttackTraceTimer);

    FTimerHandle Handle;
    GetWorld()->GetTimerManager().SetTimer(Handle, this, &AWeaponMelee::ClearHittedActors, 0.1f, false, 0.1f);
}

void AWeaponMelee::ApplyDamage(AActor* Target)
{
    if (Target)
    {
        Target->TakeDamage(20, FDamageEvent(UDamageType::StaticClass()), nullptr, nullptr);
    }

}

void AWeaponMelee::ClearHittedActors()
{
    AlreadyHittedActors.Empty();
    AlreadyHittedActors.Add(ItemOwner);
}

void AWeaponMelee::PlayAttackSound_Implementation()
{
    USoundCue* AttackSound = GetRandomFromArray(ItemInfo.WeaponStats.AttackSounds);

    if (AttackSound)
    {
        FVector Location = GetActorLocation();

        UGameplayStatics::PlaySoundAtLocation(this, AttackSound, Location);
    }
}

void AWeaponMelee::Attack_Implementation(bool IsHeavyAttack)
{
    

    TArray<UAnimMontage*> AttackArray;
    if (IsHeavyAttack)
    {
        AttackArray = ItemInfo.WeaponStats.PowerAttacks;
    }
    else
    {
        AttackArray = ItemInfo.WeaponStats.BasicAttacks;
    }
    if (ItemOwner)
    {
        if (AttackArray.Num() == 0)
        {
            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Empty array!");
            return;
        }
            
        if (CurrentCombo > AttackArray.Num() - 1)
        {
            CurrentCombo = 0;
        }

        UAnimMontage* AttackMontage = AttackArray[CurrentCombo];
        if (AttackMontage)
        {
            IBaseCharacterInterface::Execute_Server_PlayMontage(ItemOwner, AttackMontage);
        } 
    }

    IncrementComboCounter();
}

void AWeaponMelee::IncrementComboCounter()
{
    ++CurrentCombo;

    GetWorld()->GetTimerManager().SetTimer(ComboTimer, this, 
        &AWeaponMelee::ClearComboCounter, 0.f, false, ComboCounterClearDelay);
}

void AWeaponMelee::ClearComboCounter()
{
    CurrentCombo = 0;
}

