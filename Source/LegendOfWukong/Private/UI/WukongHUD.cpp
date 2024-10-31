// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WukongHUD.h"

#include "AttributeSets/WukongAttributeSet.h"

void AWukongHUD::BindDelegates(UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet) const
{
	
	const UWukongAttributeSet* WukongAttributeSet = Cast<UWukongAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	WukongAttributeSet->GetStaminaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnStaminaChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	WukongAttributeSet->GetMaxStaminaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxStaminaChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	WukongAttributeSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	WukongAttributeSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	});
}
