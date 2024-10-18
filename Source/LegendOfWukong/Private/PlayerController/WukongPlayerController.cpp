// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/WukongPlayerController.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayAbilitySpec.h"
#include "InputActionValue.h"
#include "Characters/WukongCharacter.h"
#include "DataAssets/InputDataAsset.h"
#include "GameFramework/Character.h"
#include "WukongGameplayTags/WukongGameplayTags.h"


void AWukongPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AWukongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	check(InputDataAsset);
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputDataAsset->MappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(InputDataAsset->MoveAction, ETriggerEvent::Triggered, this, &AWukongPlayerController::Move);
		EnhancedInputComponent->BindAction(InputDataAsset->LookAction, ETriggerEvent::Triggered, this, &AWukongPlayerController::Look);
	

		EnhancedInputComponent->BindAction(InputDataAsset->JumpAction, ETriggerEvent::Started, this, &AWukongPlayerController::BeginJump);
		EnhancedInputComponent->BindAction(InputDataAsset->JumpAction, ETriggerEvent::Completed, this, &AWukongPlayerController::EndJump);
	}
}

void AWukongPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AWukongPlayerController::Look(const FInputActionValue& Value)
{
	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		const FVector2D LookAxisVector = Value.Get<FVector2D>();
	
		if(LookAxisVector.X != 0)
		{
			ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		}

		if(LookAxisVector.Y != 0)
		{
			ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
		}
	}
}

void AWukongPlayerController::BeginJump(const FInputActionValue& Value)
{
	AWukongCharacter* WukongCharacter = Cast<AWukongCharacter>(GetCharacter());
	UAbilitySystemComponent* ASC = WukongCharacter->GetAbilitySystemComponent();
	for(const FGameplayAbilitySpec& AbilitySpec: ASC->GetActivatableAbilities())
	{
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(WukongGameplayTags::Player_Ability_Jump))
		{
			ASC->TryActivateAbility(AbilitySpec.Handle);
			return;
		}
	}
}

void AWukongPlayerController::EndJump(const FInputActionValue& Value)
{
	GetCharacter()->StopJumping();
}



