// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayMechanics/Items/WeaponMelee.h"

#include "Components/SceneComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"


#include "Character/SoulsBaseCharacter.h"

AWeaponMelee::AWeaponMelee()
{


   // SetActorTickEnabled(false);

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

