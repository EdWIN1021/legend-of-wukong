// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WukongCharacter.h"
#include "AbilitySystemComponent.h"
#include "Components/Combat/LockOnComponent.h"
#include "PlayerState/WukongPlayerState.h"
#include "PlayerController/WukongPlayerController.h"
#include "UI/WukongHUD.h"

AWukongCharacter::AWukongCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	LockOnComp = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockonComp"));
}

void AWukongCharacter::BeginPlay()
{
	Super::BeginPlay();
	WukongAnimInstance = Cast<UWukongAnimInstance>(GetMesh()->GetAnimInstance());
}

void AWukongCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AWukongPlayerState* WukongPlayerState = Cast<AWukongPlayerState>(GetPlayerState()))
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

AWukongHUD* AWukongCharacter::GetWukongHUD()
{
	AWukongPlayerController* WukongPlayerController =  Cast<AWukongPlayerController>(GetController());
	return Cast<AWukongHUD>(WukongPlayerController->GetHUD());
}









