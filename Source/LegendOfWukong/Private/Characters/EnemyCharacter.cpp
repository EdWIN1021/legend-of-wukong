// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/EnemyCharacter.h"



AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
