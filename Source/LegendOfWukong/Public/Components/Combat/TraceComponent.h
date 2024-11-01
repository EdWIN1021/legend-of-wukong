// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTraceSockets.h"
#include "Components/ActorComponent.h"
#include "TraceComponent.generated.h"


class UGameplayEffect;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEGENDOFWUKONG_API UTraceComponent : public UActorComponent
{

	GENERATED_BODY()

public:	
	UTraceComponent();

	TWeakObjectPtr<USkeletalMeshComponent> WeaponMesh;
		
	UPROPERTY(EditAnywhere)
	TArray<FTraceSockets> Sockets;
	
	UPROPERTY(EditAnywhere)
	double BoxCollisionLength = 30.0;

	UPROPERTY(EditAnywhere)
	bool bDebugMode = false;

	TArray<TWeakObjectPtr<AActor>> TargetsToIgnore;

	UFUNCTION(BlueprintCallable)
	void HandleResetAttack();

	UPROPERTY(VisibleAnywhere)
	bool bIsAttacking = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float GetOwnerDamage(AActor* InOwner);
};
