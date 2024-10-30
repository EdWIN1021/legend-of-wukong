// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerController.h"
#include "WukongPlayerController.generated.h"

class UDataAsset_Input;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class LEGENDOFWUKONG_API AWukongPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UDataAsset_Input* InputDataAsset;

protected:

	/* Character input functions  */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	void BeginJump();
	void EndJump();
	
	void Sprint();
	void EndSprint();
	
	void Pad();
	
	const float JumpCost = 5.0f;

private:
	/* Finds and returns an input action associated with the specified gameplay tag */
	UInputAction* FindInputActionByTag(const FGameplayTag& InputTag);
};
