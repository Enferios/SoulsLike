// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayMechanics/Interaction/InteractionInterface.h"
#include "DataTypes/ItemInfo.h"
#include "Master_Pickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;
struct FInteractableInfo;

UCLASS()
class SOULSRPG_API AMaster_Pickup : public AActor,
	public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMaster_Pickup();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup | Components")
	USphereComponent* OverlapSphere;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup | Components")
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Pickup | Info")
	FInteractableInfo PickupInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Pickup | Info")
	FItemInfo ItemInfo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	void StartFocused();
	virtual void StartFocused_Implementation();
	void EndFocused();
	virtual void EndFocused_Implementation();
	void Interact(AActor* Interactor);
	virtual void Interact_Implementation(AActor* Interactor);
	FText GetInteractableName();
	virtual FText GetInteractableName_Implemetation();

	FText GetInteractableText();
	FText GetInteractableText_Implementation();
};
