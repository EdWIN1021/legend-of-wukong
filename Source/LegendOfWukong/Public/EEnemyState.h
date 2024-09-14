// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum  EEnemyState
{
	Idle UMETA(DisplayName = "Idle"),
	GameOver UMETA(DisplayName = "GameOver"),
	Charge UMETA(DisplayName = "Charge"),
	Melee UMETA(DisplayName = "Melee"),
};
