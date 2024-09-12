// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"

#include "Kismet/KismetMathLibrary.h"


AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyCharacter::FacingPlayer(float DeltaTime)
{
	FVector Location = GetActorLocation();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* PlayerPawn = PlayerController->GetPawn();
	FVector PlayerLocation = PlayerPawn->GetActorLocation();

	FRotator DesiredRotation = UKismetMathLibrary::FindLookAtRotation(
	Location, PlayerLocation
	);

	FRotator CurrentRotation = GetActorRotation();
	FRotator NewRotation = UKismetMathLibrary::RInterpTo_Constant(
			CurrentRotation,
			DesiredRotation,
			DeltaTime,
			Speed
	);
	
	SetActorRotation(FRotator(CurrentRotation.Pitch, NewRotation.Yaw, CurrentRotation.Roll));
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// FacingPlayer(DeltaTime);
}
