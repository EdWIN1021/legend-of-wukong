// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "Components/Combat/TraceComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"

ABaseCharacter::ABaseCharacter()
{
	TraceComp = CreateDefaultSubobject<UTraceComponent>(TEXT("TraceComp"));
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseCharacter::InitializeAttributes() const
{
	if(GetAbilitySystemComponent() && InitialAttributes)
	{
		const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
		const FGameplayEffectSpecHandle  SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InitialAttributes, 1.0f, ContextHandle);
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void ABaseCharacter::InitializeAbilities() const
{
	check(AbilityDataAsset);
	for(auto& AbilityInfo : AbilityDataAsset->AbilitySet){
		FGameplayAbilitySpec AbilitySpec(AbilityInfo.Ability);
		AbilitySpec.SourceObject = AbilitySystemComponent->GetAvatarActor();
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityInfo.Tag);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}


