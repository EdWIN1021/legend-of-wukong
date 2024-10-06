// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/WukongPlayerController.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"


void AWukongPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AWukongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AWukongPlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AWukongPlayerController::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWukongPlayerController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWukongPlayerController::Look);
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

void AWukongPlayerController::Jump(const FInputActionValue& Value)
{
	
}

void AWukongPlayerController::StopJumping(const FInputActionValue& Value)
{
	
}



