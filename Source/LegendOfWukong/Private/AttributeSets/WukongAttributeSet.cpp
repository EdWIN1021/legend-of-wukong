// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSets/WukongAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Characters/BaseCharacter.h"

UWukongAttributeSet::UWukongAttributeSet()
{
	
}

void UWukongAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetInComingDamageAttribute())
	{
		float Damage = GetInComingDamage();
		SetInComingDamage(0.f);

		if(GetHealth() - Damage <= 0.f)
		{
			if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid() )
			{
				ABaseCharacter* TargetAvatarActor = Cast<ABaseCharacter>(Data.Target.AbilityActorInfo->AvatarActor.Get());
				TargetAvatarActor->OnTargetDead.Broadcast();
			}
		}
		else
		{
			SetHealth(GetHealth() - Damage);
		}
	}
}

