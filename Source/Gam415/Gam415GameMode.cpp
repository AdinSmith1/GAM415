// Copyright Epic Games, Inc. All Rights Reserved.

#include "Gam415GameMode.h"
#include "Gam415Character.h"
#include "UObject/ConstructorHelpers.h"

AGam415GameMode::AGam415GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
