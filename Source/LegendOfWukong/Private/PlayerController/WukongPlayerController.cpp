// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/WukongPlayerController.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Characters/WukongCharacter.h"
#include "DataAssets/DataAsset_Input.h"
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
		EnhancedInputComponent->BindAction(FindInputActionByTag(WukongGameplayTags::InputTag_Move), ETriggerEvent::Triggered, this, &AWukongPlayerController::Move);
		EnhancedInputComponent->BindAction(FindInputActionByTag(WukongGameplayTags::InputTag_Look), ETriggerEvent::Triggered, this, &AWukongPlayerController::Look);
		EnhancedInputComponent->BindAction(FindInputActionByTag(WukongGameplayTags::InputTag_Pad), ETriggerEvent::Started, this, &AWukongPlayerController::Pad);

		EnhancedInputComponent->BindAction(FindInputActionByTag(WukongGameplayTags::InputTag_Jump), ETriggerEvent::Started, this, &AWukongPlayerController::BeginJump);
		EnhancedInputComponent->BindAction(FindInputActionByTag(WukongGameplayTags::InputTag_Jump), ETriggerEvent::Completed, this, &AWukongPlayerController::EndJump);
		
		EnhancedInputComponent->BindAction(FindInputActionByTag(WukongGameplayTags::InputTag_Sprint), ETriggerEvent::Triggered, this, &AWukongPlayerController::Sprint);
		EnhancedInputComponent->BindAction(FindInputActionByTag(WukongGameplayTags::InputTag_Sprint), ETriggerEvent::Completed, this, &AWukongPlayerController::EndSprint);
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

void AWukongPlayerController::BeginJump()
{

	AWukongCharacter* WukongCharacter = Cast<AWukongCharacter>(GetCharacter());
	WukongCharacter->ReduceStamina(JumpCost);
	GetCharacter()->Jump();
	// AWukongCharacter* WukongCharacter = Cast<AWukongCharacter>(GetCharacter());
	// UAbilitySystemComponent* ASC = WukongCharacter->GetAbilitySystemComponent();
	// for(const FGameplayAbilitySpec& AbilitySpec: ASC->GetActivatableAbilities())
	// {
	// 	if(AbilitySpec.DynamicAbilityTags.HasTagExact(WukongGameplayTags::Player_Ability_Jump))
	// 	{
	// 		WukongCharacter->bCanRestore = false;
	// 		ASC->TryActivateAbility(AbilitySpec.Handle);
	// 		return;
	// 	}
	// }
}

void AWukongPlayerController::EndJump()
{

	GetCharacter()->StopJumping();
}

void AWukongPlayerController::Sprint()
{
}

void AWukongPlayerController::EndSprint()
{
}

void AWukongPlayerController::Pad()
{
}

UInputAction* AWukongPlayerController::FindInputActionByTag(const FGameplayTag& InputTag)
{
	check(InputDataAsset);
	for(auto& WukongAction : InputDataAsset->WukongActions )
	{
		if(WukongAction.InputTag == InputTag && WukongAction.InputAction)
		{
			return WukongAction.InputAction;
		}
	}
	return nullptr;
}



