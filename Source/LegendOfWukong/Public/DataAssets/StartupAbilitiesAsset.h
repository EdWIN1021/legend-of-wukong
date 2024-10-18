// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "StartupAbilitiesAsset.generated.h"

class UGameplayAbility;
/**
 * 
 */

USTRUCT(BlueprintType)
struct FAbilityMappings
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories = "Player"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> GameplayAbility;
};


UCLASS()
class LEGENDOFWUKONG_API UStartupAbilitiesAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameAbilities")
	TArray<FAbilityMappings> AbilityMappings;
};
