// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "GarbageSafePointersAppModuleStyle.h"

class FGarbageSafePointersAppModuleCommands : public TCommands<FGarbageSafePointersAppModuleCommands>
{
public:

	FGarbageSafePointersAppModuleCommands()
		: TCommands<FGarbageSafePointersAppModuleCommands>(TEXT("GarbageSafePointersAppModule"), NSLOCTEXT("Contexts", "GarbageSafePointersAppModule", "GarbageSafePointersAppModule application"), NAME_None, FGarbageSafePointersAppModuleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenMainWindow;
};