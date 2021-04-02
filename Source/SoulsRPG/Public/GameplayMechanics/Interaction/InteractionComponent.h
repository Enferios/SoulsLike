// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "GameplayMechanics/Pickups/InteractableInfo.h"

#include "InteractionComponent.generated.h"

struct FTimerHandle;

class ASoulsPlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOULSRPG_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	bool bDrawDebugLine;

	float TraceInterval;
	float TraceLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	AActor* InteractionTarget;

	ASoulsPlayerCharacter* PlayerCharacter;

private:

	FTimerHandle TraceTimer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, 
						FActorComponentTickFunction* ThisTickFunction) override;

	void TraceForInteract();
	void SetInteractionTarget(AActor* NewTarget);
	void ClearInteractionTarget();
	void Interact(AActor* Interactor);

	void StartTracing();
	void StopTracing();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_DrawDebugLine(FVector Start, FVector End);
};
