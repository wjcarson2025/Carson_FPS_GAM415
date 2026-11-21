// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM415_CarsonGameMode.h"
#include "GAM415_CarsonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGAM415_CarsonGameMode::AGAM415_CarsonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
