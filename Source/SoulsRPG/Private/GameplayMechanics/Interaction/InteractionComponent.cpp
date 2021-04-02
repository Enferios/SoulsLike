// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayMechanics/Interaction/InteractionComponent.h"

#include "TimerManager.h"
#include "Engine/World.h"
#include "CollisionShape.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"

#include "GameplayMechanics/Interaction/InteractionInterface.h"
#include "Character/PlayerCharacterInterface.h"
#include "Character/SoulsPlayerCharacter.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bDrawDebugLine = false;

	TraceInterval = 0.05f;
	TraceLength = 150.f;

}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TraceTimer, this,
									&UInteractionComponent::TraceForInteract,
									TraceInterval, true);
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionComponent::TraceForInteract()
{
	
	if (GetOwner() == nullptr)
		return;

	FCollisionShape Shape;
	Shape.MakeCapsule(FVector(64.f));
	
	FHitResult HitResult;
	FVector Start = GetOwner()->GetActorLocation();
	FVector End = Start + PlayerCharacter->FollowCamera->GetForwardVector() * TraceLength;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	bool IsHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat(), 
									ECollisionChannel::ECC_Visibility, Shape, CollisionParams);

	if (IsHit)
	{
		bool IsInteractable = HitResult.GetActor()->
			GetClass()->ImplementsInterface(UInteractionInterface::StaticClass());
		if (IsInteractable)
		{
			if (InteractionTarget != HitResult.GetActor())
			{
				SetInteractionTarget(HitResult.GetActor());
			}
			else
				return;
		}
		else
			ClearInteractionTarget();
	}
	else
		ClearInteractionTarget();
	if(bDrawDebugLine)
		Multicast_DrawDebugLine(Start, End);
}

void UInteractionComponent::SetInteractionTarget(AActor* NewTarget)
{
	ClearInteractionTarget();

	IInteractionInterface::Execute_StartFocused(NewTarget);
	InteractionTarget = NewTarget;

	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->Client_SetNameplateVisibility(true);

		FText NameplateText = IInteractionInterface::Execute_GetInteractableText(NewTarget);
		PlayerCharacter->Client_SetNameplateNameText(NameplateText);
	}
}

void UInteractionComponent::ClearInteractionTarget()
{
	if (InteractionTarget)
	{
		IInteractionInterface::Execute_EndFocused(InteractionTarget);
		PlayerCharacter->Client_SetNameplateVisibility(false);
	}

	InteractionTarget = nullptr;
}

void UInteractionComponent::StartTracing()
{
	GetWorld()->GetTimerManager().UnPauseTimer(TraceTimer);
}

void UInteractionComponent::StopTracing()
{
	GetWorld()->GetTimerManager().PauseTimer(TraceTimer);
	ClearInteractionTarget();
}

void UInteractionComponent::Multicast_DrawDebugLine_Implementation(FVector Start, FVector End)
{
	DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, 1.f, 10, 5.f);
}

void UInteractionComponent::Interact(AActor* Interactor)
{
	if (InteractionTarget != nullptr)
	{
		IInteractionInterface::Execute_Interact(InteractionTarget, Interactor);
	}
}
