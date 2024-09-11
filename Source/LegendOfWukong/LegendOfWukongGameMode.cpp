// Copyright Epic Games, Inc. All Rights Reserved.

#include "LegendOfWukongGameMode.h"
#include "LegendOfWukongCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALegendOfWukongGameMode::ALegendOfWukongGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
