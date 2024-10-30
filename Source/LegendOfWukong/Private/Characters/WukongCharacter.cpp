// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WukongCharacter.h"

#include "AbilitySystemComponent.h"
#include "Components/StatsComponent.h"
#include "Components/Combat/CombatComponent.h"
#include "Components/Combat/LockOnComponent.h"
#include "PlayerState/WukongPlayerState.h"
#include "EAttribute.h"
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


void AWukongCharacter::ReduceStamina(float Amount)
{

	StatsComp->Attributes[EAttribute::Stamina] -= Amount;
	StatsComp->Attributes[EAttribute::Stamina] = UKismetMathLibrary::FClamp(StatsComp->Attributes[EAttribute::Stamina], 0,StatsComp->Attributes[EAttribute::MaxStamina] );
	bCanRestore = true;

	FLatentActionInfo FunctionInfo(0, 100, TEXT("EnableStore"), this);
	
	UKismetSystemLibrary::RetriggerableDelay(
		GetWorld(),
		StaminaDelayDuration,
		FunctionInfo
	);
	
	StatsComp->OnUpdateStaminaDelegate.Broadcast(
		GetPercentage(EAttribute::Stamina, EAttribute::MaxStamina));
}

bool AWukongCharacter::HasEnoughStamina(float Cost)
{
	return StatsComp->Attributes[EAttribute::Stamina] >= Cost;
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

void AWukongCharacter::EnableStore()
{
	bCanRestore = true;
}

void AWukongCharacter::RestoreStamina()
{
	if(!bCanRestore)
	{
		return;
	}

	// UWukongAttributeSet* WukongAttributeSet = Cast<UWukongAttributeSet>(AttributeSet);
	//
	// WukongAttributeSet->SetStamina(UKismetMathLibrary::FInterpTo_Constant(
	// 	WukongAttributeSet->GetStamina(),
	// 	WukongAttributeSet->GetMaxStamina(),
	// 	GetWorld()->DeltaTimeSeconds,
	// 	StaminaRestoreRate
	// 	));
	
	StatsComp->Attributes[EAttribute::Stamina] = UKismetMathLibrary::FInterpTo_Constant(
		StatsComp->Attributes[EAttribute::Stamina],
		StatsComp->Attributes[EAttribute::MaxStamina],
		GetWorld()->DeltaTimeSeconds,
		StaminaRestoreRate
		);
	
	StatsComp->OnUpdateStaminaDelegate.Broadcast(
		GetPercentage(EAttribute::Stamina, EAttribute::MaxStamina));
}

void AWukongCharacter::Sprint()
{
	if(!HasEnoughStamina(SprintCost))
	{
		Walk();
		return;
	}

	if(GetCharacterMovement()->Velocity.Equals(FVector::ZeroVector, 1))
	{
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	ReduceStamina(SprintCost);
}

void AWukongCharacter::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AWukongCharacter::Pad()
{
	bCanTakeDamage = false;
	ReduceStamina(PadCost);
	FVector Direction = (GetCharacterMovement()->Velocity.Length() < 1) ? GetActorForwardVector() : GetLastMovementInputVector();
	FRotator Rotation = UKismetMathLibrary::MakeRotFromX(Direction);
	SetActorRotation(Rotation);
	float Duration = PlayAnimMontage(PadAnimMontage);
	FTimerHandle PadTimerHandle;
	GetWorldTimerManager().SetTimer(PadTimerHandle, this, &AWukongCharacter::FinishPadAnim, Duration, false);
}






