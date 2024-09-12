// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FacingPlayerComponent.generated.h"

UCLASS()
class LEGENDOFWUKONG_API AFacingPlayerComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	AFacingPlayerComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
