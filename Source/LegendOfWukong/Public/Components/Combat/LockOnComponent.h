// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/EnemyCharacter.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LockOnComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnUpdatedTargetSignature,
	ULockOnComponent,
	OnUpdatedTargetDelegate,
	AActor*,
	NewTargetActorRef
);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEGENDOFWUKONG_API ULockOnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULockOnComponent();

	/** The actor currently being targeted. */
	AEnemyCharacter* TargetActor;
	
	UPROPERTY(BlueprintAssignable)
	FOnUpdatedTargetSignature OnUpdatedTargetDelegate;

	void EndLockOn();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	void StartLockOn(float Radius = 750.f);


	UFUNCTION(BlueprintCallable)
	void ToggleLockOn(float Radius = 750.f);
	
private:
	/** The character that owns this component. */
	TObjectPtr<ACharacter> OwnerPawn;

	/** The player controller for the current player. */
	TWeakObjectPtr<APlayerController> Controller;

	/** The movement component of the owning character. */
	TWeakObjectPtr<UCharacterMovementComponent> MovementComponent;

	/** The spring arm component for camera adjustments. */
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	double AutoEndLockOnDistance = 1000.f;
};
