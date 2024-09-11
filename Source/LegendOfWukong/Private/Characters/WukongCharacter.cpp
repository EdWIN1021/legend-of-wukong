// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WukongCharacter.h"

void AWukongCharacter::BeginPlay()
{
	Super::BeginPlay();
	WukongAnim = Cast<UWukongAnimInstance>(GetMesh()->GetAnimInstance());
}
