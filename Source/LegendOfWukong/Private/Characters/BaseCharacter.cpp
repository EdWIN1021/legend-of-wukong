// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "Components/StatsComponent.h"
#include "Components/Combat/TraceComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"

ABaseCharacter::ABaseCharacter()
{
	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComp"));
	TraceComp = CreateDefaultSubobject<UTraceComponent>(TEXT("TraceComp"));
}

float ABaseCharacter::GetPercentage(EAttribute Current, EAttribute Max)
{
	return StatsComp->Attributes[Current] / StatsComp->Attributes[Max];
}

void ABaseCharacter::ReduceHealth(float Amount)
{
	if(StatsComp->Attributes[EAttribute::Health] <= 0)
	{
		return;
	}
    	
	StatsComp->Attributes[EAttribute::Health] -= Amount;
	StatsComp->Attributes[EAttribute::Health] = UKismetMathLibrary::FClamp(StatsComp->Attributes[EAttribute::Health], 0,StatsComp->Attributes[EAttribute::MaxHealth]);

	StatsComp->OnUpdateHealthUIDelegate.Broadcast(
	GetPercentage(EAttribute::Health, EAttribute::MaxHealth));

	if(StatsComp->Attributes[EAttribute::Health] == 0 )
	{
		
		StatsComp->OnZeroHealthDelegate.Broadcast(true);
	}
}

float ABaseCharacter::ApplyDamage()
{
	return StatsComp->Attributes[EAttribute::Strength];
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
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
	}
}
