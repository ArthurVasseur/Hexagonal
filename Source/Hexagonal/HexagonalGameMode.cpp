// Copyright Epic Games, Inc. All Rights Reserved.

#include "HexagonalGameMode.h"
#include "HexagonalPlayerController.h"
#include "HexagonalCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHexagonalGameMode::AHexagonalGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AHexagonalPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}