// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WukongPlayerController.generated.h"

class UInputDataAsset;
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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UInputDataAsset* InputDataAsset;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void BeginJump(const FInputActionValue& Value);
	void EndJump(const FInputActionValue& Value);
};
