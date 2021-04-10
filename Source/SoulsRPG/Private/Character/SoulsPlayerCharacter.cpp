// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SoulsPlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"

#include "GameplayMechanics/Interaction/InteractionComponent.h"
#include "GameplayMechanics/Items/Master_Item.h"
#include "GameplayMechanics/Stats/CharacterStatsComponent.h"
#include "Animation/HumanAnimInstance.h"
#include "Controller/SoulsPlayerController.h"
#include "HUD/GameOverlay.h"




ASoulsPlayerCharacter::ASoulsPlayerCharacter()
{
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
    GetCharacterMovement()->MaxWalkSpeed = 400.f;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
    SpringArm->TargetArmLength = 300.f;
    SpringArm->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject <UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(SpringArm, SpringArm->SocketName);

    InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT
                                                    ("InteractionComponent"));

    GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, 
                                                ECollisionResponse::ECR_Ignore);
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera,
                                                ECollisionResponse::ECR_Ignore);

    TurnRate = 60.f;
    LookUpRate = 60.f;

    bInputEnabled = true;
    bMovementEnabled = true;
    bIsSprinting = false;
   
    WeaponMode = ECharacterWeaponMode::CWM_None;

    Tags.Add("Player");
}

void ASoulsPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    InteractionComponent->PlayerCharacter = this;

    PlayerController = Cast<ASoulsPlayerController>(GetController());

    CharacterStats->OnCharacterDeath.AddDynamic(this, &ASoulsPlayerCharacter::Death);
}

void ASoulsPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Turn", this, &ASoulsPlayerCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &ASoulsPlayerCharacter::LookUp);

    PlayerInputComponent->BindAxis("MoveForward", this, &ASoulsPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASoulsPlayerCharacter::MoveRight);

    PlayerInputComponent->BindAction("Shift", EInputEvent::IE_Pressed, this,
                                     &ASoulsPlayerCharacter::ShiftKeyPressed);
    PlayerInputComponent->BindAction("Shift", EInputEvent::IE_Released, this,
                                     &ASoulsPlayerCharacter::ShiftKeyReleased);
    PlayerInputComponent->BindAction("Spacebar", EInputEvent::IE_Pressed, this,
                                     &ASoulsPlayerCharacter::SpacebarKeyPressed);
    PlayerInputComponent->BindAction("LMB", EInputEvent::IE_Pressed, this,
                                     &ASoulsPlayerCharacter::LMBDown);
    PlayerInputComponent->BindAction("LMB", EInputEvent::IE_Released, this,
                                     &ASoulsPlayerCharacter::LMBUp);
    PlayerInputComponent->BindAction("FKey", EInputEvent::IE_Pressed, this,
                                     &ASoulsPlayerCharacter::FKeyPressed);
    PlayerInputComponent->BindAction("DrawMainWeapon", EInputEvent::IE_Pressed, this,
                                    &ASoulsPlayerCharacter::DrawMainWeaponPressed);
}

void ASoulsPlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ASoulsPlayerCharacter, EquippedItems);
    DOREPLIFETIME(ASoulsPlayerCharacter, WeaponMode);
    DOREPLIFETIME(ASoulsPlayerCharacter, bIsMoving);
}

void ASoulsPlayerCharacter::MoveForward(float AxisValue)
{
    bool bCanMove = AxisValue != 0.f;

    if (bCanMove)
    {
        FRotator ControllerRotation = GetControlRotation();
        FRotator YawRotation = FRotator(0.f, ControllerRotation.Yaw, 0.f);
        FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        AddMovementInput(Direction, AxisValue);
    }

    Server_CheckIsMoving();
}

void ASoulsPlayerCharacter::MoveRight(float AxisValue)
{
    bool bCanMove = AxisValue != 0.f;

    if (bCanMove)
    {
        FRotator ControllerRotation = GetControlRotation();
        FRotator YawRotation = FRotator(0.f, ControllerRotation.Yaw, 0.f);
        FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(Direction, AxisValue);
    }
}

void ASoulsPlayerCharacter::LookUp(float AxisValue)
{
    bool bCanRotate = AxisValue != 0.f;

    if (bCanRotate)
    {
        float DeltaPitchRotation = AxisValue * GetWorld()->GetDeltaSeconds();
        DeltaPitchRotation *= LookUpRate;

        AddControllerPitchInput(DeltaPitchRotation);
    }
    
}

void ASoulsPlayerCharacter::Turn(float AxisValue)
{
    bool bCanRotate = AxisValue != 0.f;

    if (bCanRotate)
    {
        float DeltaPitchRotation = AxisValue * GetWorld()->GetDeltaSeconds();
        DeltaPitchRotation *= LookUpRate;

        AddControllerYawInput(DeltaPitchRotation);
    }
}

void ASoulsPlayerCharacter::ShiftKeyPressed()
{
    if (CanMove())
    {
        Server_ActivateSprintMode();
    }
}

void ASoulsPlayerCharacter::ShiftKeyReleased()
{
    Server_DeactivateSprintMode();
}

void ASoulsPlayerCharacter::SpacebarKeyPressed()
{
    if (CanMove() && !bIsRolling)
    {
        Server_TryRolling();
    }
}

void ASoulsPlayerCharacter::FKeyPressed()
{
    if (bInputEnabled)
    {
        Server_TryInteract();
    }
}

void ASoulsPlayerCharacter::DrawMainWeaponPressed()
{
    if (WeaponMode == ECharacterWeaponMode::CWM_None)
    {
        Server_TryDrawWeapon();
    }
    else
        Server_TrySheathWeapon();
}

void ASoulsPlayerCharacter::LMBDown()
{
    if (CanMove() && !bIsAttacking)
    {
        if (AttackChargingMontage)
            Server_TryChargeAttack();
    }
}

void ASoulsPlayerCharacter::LMBUp()
{

        Server_TryAttack();
}


bool ASoulsPlayerCharacter::CanMove()
{
    return true;
}

void ASoulsPlayerCharacter::Server_ActivateSprintMode_Implementation()
{
    bIsSprinting = true;

    GetCharacterMovement()->MaxWalkSpeed = 600.f;

    Multicast_SetWalkSpeed(600.f);
}

void ASoulsPlayerCharacter::Server_DeactivateSprintMode_Implementation()
{
    GetCharacterMovement()->MaxWalkSpeed = 400.f;

    Multicast_SetWalkSpeed(400.f);
}

void ASoulsPlayerCharacter::Multicast_SetWalkSpeed_Implementation(float NewSpeed)
{
    GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void ASoulsPlayerCharacter::Server_TryRolling_Implementation()
{
    if (CanMove())
    {
        bIsAttacking = false;
        bIsRolling = true;

        Multicast_PlayMontage(GetMesh(), RollingMontage, "None");
    }
}



void ASoulsPlayerCharacter::Server_TryChargeAttack_Implementation()
{
    if (WeaponMode == ECharacterWeaponMode::CWM_None)
        return;

    if (CanMove())
    {
        Multicast_PlayMontage(GetMesh(), AttackChargingMontage, "None");
        bIsAttacking = true;
    }
}

void ASoulsPlayerCharacter::Server_TryAttack_Implementation()
{
    if (WeaponMode == ECharacterWeaponMode::CWM_None)
        return;

    if (bIsAttacking)
    {
        if (bIsHeavyAttackCharged)
        {
            Multicast_PlayMontage(GetMesh(), AttackHeavyMontage, "None");
        }
        else
        {
            Multicast_PlayMontage(GetMesh(), AttackLightMontage, "None");
        }
    }
}

void ASoulsPlayerCharacter::Client_SetNameplateVisibility_Implementation(bool NewVisibility)
{
    if (PlayerController)
    {
        if (PlayerController->GameOverlayWidget)
        {
            PlayerController->GameOverlayWidget->SetNameplateVisibility(NewVisibility);
        }
    } 
}

void ASoulsPlayerCharacter::Client_SetNameplateNameText_Implementation(const FText& NewText)
{
    if (PlayerController)
    {
        if (PlayerController->GameOverlayWidget)
        {
            PlayerController->GameOverlayWidget->SetNameplateNameText(NewText);
        }
    }

}

void ASoulsPlayerCharacter::Server_TryInteract_Implementation()
{
    InteractionComponent->Interact(this);
}

void ASoulsPlayerCharacter::OnRep_EquippedItems()
{

}

void ASoulsPlayerCharacter::EquipItem_Implementation(const FItemInfo& Item)
{
    if (Item.ItemClass != nullptr)
    {
        EquippedItems.MainWeapon = GetWorld()->SpawnActor<AMaster_Item>(Item.ItemClass, FVector(0.f), FRotator(0.f), FActorSpawnParameters());
        EquippedItems.MainWeapon->AttachToComponent(TwoHandedWeaponEquipSocket, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
        EquippedItems.MainWeapon->ItemInfo = Item;
        EquippedItems.MainWeapon->ItemOwner = this;

        Multicast_PlayMontage(GetMesh(), PickupMontage);
    }
    else
        UE_LOG(LogTemp, Error, TEXT("Item class for creating is not valid!"
            "Character->EquipItem()"));
}

void ASoulsPlayerCharacter::OnRep_WeaponMode()
{
    if (AnimInstance)
        AnimInstance->WeaponMode = WeaponMode;
}

void ASoulsPlayerCharacter::EnableAttackCollision_Implementation()
{
    if (EquippedItems.MainWeapon)
    {
        EquippedItems.MainWeapon->Server_TryEnableCombatTracing();
    }
}

void ASoulsPlayerCharacter::DisableAttackCollision_Implementation()
{
    if (EquippedItems.MainWeapon)
    {
        EquippedItems.MainWeapon->Server_TryDisableCombatTracing();
    }
}

void ASoulsPlayerCharacter::Server_TryDrawWeapon_Implementation()
{
    if (EquippedItems.MainWeapon == nullptr)
        return;

    Multicast_PlayMontage(GetMesh(), WeaponDrawMontage, "Equip");
}

void ASoulsPlayerCharacter::Server_TrySheathWeapon_Implementation()
{

    Multicast_PlayMontage(GetMesh(), WeaponDrawMontage, "Unequip");
}


void ASoulsPlayerCharacter::Death()
{
    Super::Death();

    if (DeathMontage)
    {
        Multicast_PlayMontage(GetMesh(), DeathMontage);
    }
}

void ASoulsPlayerCharacter::OnRep_IsMoving()
{
    AnimInstance->bIsMoving = bIsMoving;
}

void ASoulsPlayerCharacter::Server_CheckIsMoving_Implementation()
{
    FVector CurrentVelocity = GetCharacterMovement()->GetLastUpdateVelocity();
    bIsMoving = CurrentVelocity.Size() > 0.f;
}

void ASoulsPlayerCharacter::EquipWeaponNotify_Implementation()
{
    Server_TrySetWeaponMode(ECharacterWeaponMode::CWM_Longsword);
}

void ASoulsPlayerCharacter::UnequipWeaponNotify_Implementation()
{
    Server_TrySetWeaponMode(ECharacterWeaponMode::CWM_None);
}

void ASoulsPlayerCharacter::Server_TrySetWeaponMode_Implementation(ECharacterWeaponMode NewMode)
{
    WeaponMode = NewMode;

    switch (WeaponMode)
    {
        case ECharacterWeaponMode::CWM_Longsword:
            EquippedItems.MainWeapon->AttachToComponent(TwoHandedWeaponHandSocket,
                 FAttachmentTransformRules::SnapToTargetNotIncludingScale);
            break;
        case ECharacterWeaponMode::CWM_None:
            EquippedItems.MainWeapon->AttachToComponent(TwoHandedWeaponEquipSocket,
                                FAttachmentTransformRules::SnapToTargetNotIncludingScale);
            break;
    }

}
