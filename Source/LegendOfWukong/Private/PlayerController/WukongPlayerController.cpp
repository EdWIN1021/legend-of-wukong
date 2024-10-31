// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/WukongPlayerController.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "AttributeSets/WukongAttributeSet.h"
#include "Characters/WukongCharacter.h"
#include "DataAssets/DataAsset_Input.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerState/WukongPlayerState.h"
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

		EnhancedInputComponent->BindAction(FindInputActionByTag(WukongGameplayTags::InputTag_Jump), ETriggerEvent::Started, this, &AWukongPlayerController::Jump);
		
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

void AWukongPlayerController::Jump()
{
	ActivateAbilityByTag(WukongGameplayTags::Player_Ability_Jump, 5.0f);
}

void AWukongPlayerController::Sprint()
{
	/** Don't activate if Player is not moving */
	if(Cast<AWukongCharacter>(GetCharacter())->GetCharacterMovement()->Velocity.Equals(FVector::Zero(), 1)) return;
	ActivateAbilityByTag(WukongGameplayTags::Player_Ability_Sprint, 1.0f);
}

void AWukongPlayerController::EndSprint()
{
	OnFinishSprint.Broadcast();
}

void AWukongPlayerController::Pad()
{
	ActivateAbilityByTag(WukongGameplayTags::Player_Ability_Pad, 10.f);
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

void AWukongPlayerController::ActivateAbilityByTag(const FGameplayTag& AbilityTag, float Cost)
{
	if(!HasEnoughStamina(Cost))
	{
		/** End Ability When Stamina is less than 0 */
		if(AbilityTag == WukongGameplayTags::Player_Ability_Sprint)
		{
			OnFinishSprint.Broadcast();
		}
		return;
	}
	
	AWukongCharacter* WukongCharacter = Cast<AWukongCharacter>(GetCharacter());
	UAbilitySystemComponent* ASC = WukongCharacter->GetAbilitySystemComponent();
	
	for(const FGameplayAbilitySpec& AbilitySpec: ASC->GetActivatableAbilities())
	{
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(AbilityTag))
		{
			ASC->TryActivateAbility(AbilitySpec.Handle);
			return;
		}
	}
}

bool AWukongPlayerController::HasEnoughStamina(float Cost)
{
	AWukongCharacter* WukongCharacter = Cast<AWukongCharacter>(GetCharacter());
	UWukongAttributeSet* WukongAttributeSet = Cast<UWukongAttributeSet>(WukongCharacter->GetAttributeSet());
	return  WukongAttributeSet->GetStamina() > Cost;
}



