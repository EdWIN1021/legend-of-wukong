// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TraceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEGENDOFWUKONG_API UTraceComponent : public UActorComponent
{

	GENERATED_BODY()

public:	
	UTraceComponent();

	USkeletalMeshComponent* SkeletakMesh;

	UPROPERTY(EditAnywhere)
	FName Start;

	UPROPERTY(EditAnywhere)
	FName End;

	UPROPERTY(EditAnywhere)
	FName Rotation;

	UPROPERTY(EditAnywhere)
	double BoxCollisionLength = 30.0;

	UPROPERTY(EditAnywhere)
	bool bDebugMode = false;

	TArray<AActor*> TargetsToIgnore;

	UFUNCTION(BlueprintCallable)
	void HandleResetAttack();

	UPROPERTY(VisibleAnywhere)
	bool bIsAttacking = false;
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
