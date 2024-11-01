// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "WukongAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */

UCLASS()
class LEGENDOFWUKONG_API UWukongAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UWukongAttributeSet();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UWukongAttributeSet, Health);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UWukongAttributeSet, MaxHealth);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UWukongAttributeSet, Stamina);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UWukongAttributeSet, MaxStamina);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UWukongAttributeSet, Strength);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Attributes")
	FGameplayAttributeData InComingDamage;
	ATTRIBUTE_ACCESSORS(UWukongAttributeSet, InComingDamage);

	

	

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
