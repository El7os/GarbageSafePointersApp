// Copyright Epic Games, Inc. All Rights Reserved.

#include "GarbageSafePointersAppApp.h"
#include "GarbageSafePointersAppModule/Public/GarbageSafePointersAppModule.h"

#include "Runtime/Launch/Public/RequiredProgramMainCPPInclude.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "Framework/Docking/WorkspaceItem.h"
#include "Styling/StarshipCoreStyle.h"

IMPLEMENT_APPLICATION(GarbageSafePointersApp, "GarbageSafePointersApp");

#define LOCTEXT_NAMESPACE "GarbageSafePointersApp"

namespace WorkspaceMenu
{
	TSharedRef<FWorkspaceItem> DeveloperMenu = FWorkspaceItem::NewGroup(LOCTEXT("DeveloperMenu", "Developer"));
}


int RunGarbageSafePointersApp( const TCHAR* CommandLine )
{
	FTaskTagScope TaskTagScope(ETaskTag::EGameThread);

	// start up the main loop
	GEngineLoop.PreInit(CommandLine);

	// Make sure all UObject classes are registered and default properties have been initialized
	ProcessNewlyLoadedUObjects();
	
	// Tell the module manager it may now process newly-loaded UObjects when new C++ modules are loaded
	FModuleManager::Get().StartProcessingNewlyLoadedObjects();

	// crank up a normal Slate application using the platform's standalone renderer
	FSlateApplication::InitializeAsStandaloneApplication(GetStandardStandaloneRenderer());

	FSlateApplication::InitHighDPI(true);

	// set the application name
	FGlobalTabmanager::Get()->SetApplicationTitle(LOCTEXT("AppTitle", "GarbageSafePointersApp"));
	FAppStyle::SetAppStyleSetName(FStarshipCoreStyle::GetCoreStyle().GetStyleSetName());

	// launch the main window of the GarbageSafePointersApp module
	FGarbageSafePointersAppModule& GarbageSafePointersAppModule = FModuleManager::LoadModuleChecked<FGarbageSafePointersAppModule>(FName("GarbageSafePointersAppModule"));
	GarbageSafePointersAppModule.AppStarted();
	
	// loop while the server does the rest
	while (!IsEngineExitRequested())
	{
		BeginExitIfRequested();

		FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
		FStats::AdvanceFrame(false);
		FTSTicker::GetCoreTicker().Tick(FApp::GetDeltaTime());
		FSlateApplication::Get().PumpMessages();
		FSlateApplication::Get().Tick();
		FPlatformProcess::Sleep(0.01);

		GFrameCounter++;
	}

	FCoreDelegates::OnExit.Broadcast();
	FSlateApplication::Shutdown();
	FModuleManager::Get().UnloadModulesAtShutdown();

	GEngineLoop.AppPreExit();
	GEngineLoop.AppExit();

	return 0;
}

#undef LOCTEXT_NAMESPACE
