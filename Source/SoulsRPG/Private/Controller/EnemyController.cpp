// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/EnemyController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/EnemyCharacterInterface.h"

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "BT init succeed");
	}
    
}

void AEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	LookAtTarget();
}

void AEnemyController::SetTarget_Implementation(AActor* NewTarget)
{
	CurrentTarget = NewTarget;
}

void AEnemyController::ClearTarget()
{
	CurrentTarget = nullptr;

	IEnemyCharacterInterface::Execute_ClearTarget(GetPawn());
}

void AEnemyController::LookAtTarget()
{
	APawn* ControlledPawn = GetPawn();

	if (CurrentTarget && ControlledPawn)
	{
		FVector TargetLocation = CurrentTarget->GetActorLocation();
		FVector PawnLocation = ControlledPawn->GetActorLocation();
		float LookAtRotationYaw = UKismetMathLibrary::FindLookAtRotation(PawnLocation, TargetLocation).Yaw;
		FRotator CurrentPawnRotation = ControlledPawn->GetActorRotation();
		FRotator LookAtRotation = FRotator(CurrentPawnRotation.Pitch, 
								LookAtRotationYaw, CurrentPawnRotation.Roll);

		ControlledPawn->SetActorRotation(LookAtRotation);
	}
}

void AEnemyController::SelectAttack_Implementation()
{
	IEnemyCharacterInterface::Execute_SelectAttack(GetPawn());
}