// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayMechanics/Pickups/Master_Pickup.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"

#include "Character/PlayerCharacterInterface.h"
#include "HUD/NameplateWidgetInterface.h"

// Sets default values
AMaster_Pickup::AMaster_Pickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SetReplicateMovement(true);

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PickupMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	PickupMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic,
											ECollisionResponse::ECR_Block);
	PickupMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic,
											ECollisionResponse::ECR_Block);
	PickupMesh->SetSimulatePhysics(true);
	SetRootComponent(PickupMesh);
	

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	OverlapSphere->InitSphereRadius(64.f);
	OverlapSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,
											ECollisionResponse::ECR_Block);
	OverlapSphere->SetupAttachment(GetRootComponent());

	PickupInfo.Name.FromString("JustTesting");

}

// Called when the game starts or when spawned
void AMaster_Pickup::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMaster_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMaster_Pickup::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMaster_Pickup, PickupInfo);
}

void AMaster_Pickup::StartFocused_Implementation()
{
}

void AMaster_Pickup::EndFocused_Implementation()
{

}

void AMaster_Pickup::Interact_Implementation(AActor* Interactor)
{
	IPlayerCharacterInterface::Execute_EquipItem(Interactor, ItemInfo);
	SetLifeSpan(0.3f);
}

FText AMaster_Pickup::GetInteractableName_Implemetation()
{
	return PickupInfo.Name;
}

FText AMaster_Pickup::GetInteractableText_Implementation()
{
	return PickupInfo.Name;
}






