// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Fighter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFighter : public UInterface
{
	GENERATED_BODY()
};


class LEGENDOFWUKONG_API IFighter
{
	GENERATED_BODY()

public:
	// virtual float GetDamage(){ return  0.0f; };
};
