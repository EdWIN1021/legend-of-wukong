// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WukongCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/StatsComponent.h"
#include "Components/Combat/CombatComponent.h"
#include "Components/Combat/LockOnComponent.h"
#include "PlayerState/WukongPlayerState.h"
#include "EAttribute.h"
#include "AttributeSets/WukongAttributeSet.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerController/WukongPlayerController.h"
#include "UI/WukongHUD.h"

AWukongCharacter::AWukongCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	LockonComp = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockonComp"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComp"));
}

void AWukongCharacter::BeginPlay()
{
	Super::BeginPlay();
	WukongAnim = Cast<UWukongAnimInstance>(GetMesh()->GetAnimInstance());
}

void AWukongCharacter::PossessedBy(AController* NewController)
{
	
	Super::PossessedBy(NewController);
	AWukongPlayerState* WukongPlayerState = Cast<AWukongPlayerState>(GetPlayerState());

	if (WukongPlayerState)
	{
		/* Set up the Ability System Component and Attribute Set for the character by retrieving them from the PlayerState. */
		WukongPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(WukongPlayerState, this);
		AbilitySystemComponent = WukongPlayerState->GetAbilitySystemComponent();
		AttributeSet = WukongPlayerState->GetAttributeSet();

		/* Setup enables the HUD to display dynamic updates on character attributes and abilities, such as health. */
		AWukongHUD* WukongHUD = GetWukongHUD();
		WukongHUD->InitializedHUD();
		WukongHUD->BindDelegates(AbilitySystemComponent, AttributeSet);

		/* Initialize the character's default attributes and abilities, preparing them for gameplay. */
		InitializeAttributes();
		InitializeAbilities();
	}
}

void AWukongCharacter::FinishPadAnim()
{
	bCanTakeDamage = true;
}

AWukongHUD* AWukongCharacter::GetWukongHUD()
{
	AWukongPlayerController* WukongPlayerController =  Cast<AWukongPlayerController>(GetController());
	return Cast<AWukongHUD>(WukongPlayerController->GetHUD());
}

void AWukongCharacter::AutoEndLock(AActor* Actor)
{
	if(LockonComp->TargetActor != Actor)
	{
		return;
	}

	LockonComp->EndLockOn();
}

void AWukongCharacter::ReduceHealth(float Amount)
{
	if(!bCanTakeDamage){
		return;
	}
	
	Super::ReduceHealth(Amount);
}

void AWukongCharacter::RestoreStamina()
{
	// if(!bCanRestore)
	// {
	// 	return;
	// }
	
	UWukongAttributeSet* WukongAttributeSet = Cast<UWukongAttributeSet>(AttributeSet);
	
	WukongAttributeSet->SetStamina(UKismetMathLibrary::FInterpTo_Constant(
		WukongAttributeSet->GetStamina(),
		WukongAttributeSet->GetMaxStamina(),
		GetWorld()->DeltaTimeSeconds,
		StaminaRestoreRate
		));
}











