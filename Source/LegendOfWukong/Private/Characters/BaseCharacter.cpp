// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"

#include "Kismet/KismetMathLibrary.h"


float ABaseCharacter::ApplyDamage()
{
	return 0;
}

void ABaseCharacter::ReduceHealth(float Amount)
{
	if(Attributes[EAttribute::Health] <= 0)
	{
		return;
	}
	Attributes[EAttribute::Health] -= Amount;
	Attributes[EAttribute::Health] = UKismetMathLibrary::FClamp(Attributes[EAttribute::Health], 0,Attributes[EAttribute::MaxHealth] );
}
