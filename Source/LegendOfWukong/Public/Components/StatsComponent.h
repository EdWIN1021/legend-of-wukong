// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EAttribute.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnUpdateHealthUI,
	UStatsComponent,
	OnUpdateHealthUIDelegate,
	float,
	Percentage
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEGENDOFWUKONG_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatsComponent();
	
	UPROPERTY(EditAnywhere)
	TMap<EAttribute, float> Attributes;

	UPROPERTY(BlueprintAssignable)
	FOnUpdateHealthUI OnUpdateHealthUIDelegate;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
};