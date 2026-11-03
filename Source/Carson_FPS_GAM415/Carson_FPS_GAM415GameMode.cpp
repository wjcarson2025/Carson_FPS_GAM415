// Copyright Epic Games, Inc. All Rights Reserved.

#include "Carson_FPS_GAM415GameMode.h"
#include "Carson_FPS_GAM415Character.h"
#include "UObject/ConstructorHelpers.h"

ACarson_FPS_GAM415GameMode::ACarson_FPS_GAM415GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
