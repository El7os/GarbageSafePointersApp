// Copyright Epic Games, Inc. All Rights Reserved.

#include "GarbageSafePointersAppModule/Public/GarbageSafePointersAppModuleCommands.h"

#define LOCTEXT_NAMESPACE "FGarbageSafePointersAppModuleModule"

void FGarbageSafePointersAppModuleCommands::RegisterCommands()
{
	UI_COMMAND(OpenMainWindow, "GarbageSafePointersAppModule", "Bring up GarbageSafePointersAppModule window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
