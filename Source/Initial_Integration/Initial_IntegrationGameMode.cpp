// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Initial_IntegrationGameMode.h"
#include "Initial_IntegrationCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInitial_IntegrationGameMode::AInitial_IntegrationGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}
