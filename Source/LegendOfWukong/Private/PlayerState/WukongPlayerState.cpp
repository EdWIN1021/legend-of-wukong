// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/WukongPlayerState.h"
#include "AbilitySystem/WukongAbilitySystemComponent.h"
#include "AttributeSets/WukongAttributeSet.h"

AWukongPlayerState::AWukongPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UWukongAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UWukongAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AWukongPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
