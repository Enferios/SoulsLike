// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayMechanics/Items/Master_Item.h"

#include "Net/UnrealNetwork.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
AMaster_Item::AMaster_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetSimulatePhysics(false);

	SetRootComponent(ItemMesh);
}

// Called when the game starts or when spawned
void AMaster_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMaster_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMaster_Item::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMaster_Item, ItemInfo);
}

void AMaster_Item::Server_TryEnableCombatTracing_Implementation()
{
}

void AMaster_Item::Server_TryDisableCombatTracing_Implementation()
{
}

