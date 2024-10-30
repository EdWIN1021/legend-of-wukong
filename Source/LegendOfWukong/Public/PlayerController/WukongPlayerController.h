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
	
	void Jump();
	
	void Sprint();
	void EndSprint();
	
	void Pad();

private:
	/**
	 * Finds and returns an input action associated with the specified gameplay tag
	 * @param InputTag The gameplay tag that identifies the InputAction.
	 */
	UInputAction* FindInputActionByTag(const FGameplayTag& InputTag);

	/**
	 * Activates an ability associated with the specified gameplay tag.
	 * @param AbilityTag The gameplay tag that identifies the ability to be activated.
	 */
	void ActivateAbilityByTag(const FGameplayTag& AbilityTag);
};
