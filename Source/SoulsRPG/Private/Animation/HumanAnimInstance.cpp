// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HumanAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Character/SoulsBaseCharacter.h"
#include "Character/PlayerCharacterInterface.h"

UHumanAnimInstance::UHumanAnimInstance()
{

}

void UHumanAnimInstance::UpdateAnimationProperties()
{
	if (Character == nullptr)
		Character = Cast<ASoulsBaseCharacter>(TryGetPawnOwner());

	if (Character)
	{
		Velocity = Character->GetVelocity().Size();
		CurrentAcceleration = Character->GetCharacterMovement()->GetCurrentAcceleration().Size();

		bIsFalling = Character->GetCharacterMovement()->IsFalling();
	}
}

void UHumanAnimInstance::EnableAttackCollision_Implementation()
{
	if (Character)
	{
		IPlayerCharacterInterface::Execute_EnableAttackCollision(Character);
	}
}

void UHumanAnimInstance::DisableAttackCollision_Implementation()
{
	if (Character)
	{
		IPlayerCharacterInterface::Execute_DisableAttackCollision(Character);
	}
}

