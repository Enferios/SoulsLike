// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DataTypes/ItemInfo.h"

#include "Master_Item.generated.h"

class UStaticMeshComponent;
class ASoulsBaseCharacter;

UCLASS()
class SOULSRPG_API AMaster_Item : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaster_Item();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ItemMesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ASoulsBaseCharacter* ItemOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemInfo ItemInfo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void Server_TryEnableCombatTracing();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void Server_TryDisableCombatTracing();

};
