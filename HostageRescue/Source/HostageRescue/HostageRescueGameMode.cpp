// Copyright Epic Games, Inc. All Rights Reserved.

#include "HostageRescueGameMode.h"
#include "HostageRescueCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHostageRescueGameMode::AHostageRescueGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
