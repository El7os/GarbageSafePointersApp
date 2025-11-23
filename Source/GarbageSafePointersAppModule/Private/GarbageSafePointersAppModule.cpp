// Copyright Epic Games, Inc. All Rights Reserved.

#include "GarbageSafePointersAppModule/Public/GarbageSafePointersAppModule.h"
#include "GarbageSafePointersAppModule/Public/GarbageSafePointersAppModuleStyle.h"
#include "GarbageSafePointersAppModule/Public/GarbageSafePointersAppModuleCommands.h"
#include "GarbageSafePointersAppModule/Public/Core/Testing.h"

#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

static const FName GarbageSafePointersAppModuleTabName("GarbageSafePointersAppModule");

#define LOCTEXT_NAMESPACE "FGarbageSafePointersAppModule"

void FGarbageSafePointersAppModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; 
	
	FGarbageSafePointersAppModuleStyle::Initialize();
	FGarbageSafePointersAppModuleStyle::ReloadTextures();

	FGarbageSafePointersAppModuleCommands::Register();
	
	AppCommands = MakeShareable(new FUICommandList);

	AppCommands->MapAction(
		FGarbageSafePointersAppModuleCommands::Get().OpenMainWindow,
		FExecuteAction::CreateRaw(this, &FGarbageSafePointersAppModule::AppStarted),
		FCanExecuteAction());
		
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(GarbageSafePointersAppModuleTabName, FOnSpawnTab::CreateRaw(this, &FGarbageSafePointersAppModule::OnSpawnMainTab))
		.SetDisplayName(LOCTEXT("FGarbageSafePointersAppModuleTabTitle", "Garbage Safe Pointers"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FGarbageSafePointersAppModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
	FGarbageSafePointersAppModuleStyle::Shutdown();

	FGarbageSafePointersAppModuleCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(GarbageSafePointersAppModuleTabName);
}

TSharedRef<SDockTab> FGarbageSafePointersAppModule::OnSpawnMainTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FGarbageSafePointersAppModule::OnSpawnMainTab")),
		FText::FromString(TEXT("GarbageSafePointersAppModule.cpp"))
		);

	const auto& Result = ConstructTestResult_General();
					
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FGarbageSafePointersAppModule::AppStarted()
{
	FGlobalTabmanager::Get()->TryInvokeTab(GarbageSafePointersAppModuleTabName);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGarbageSafePointersAppModule, GarbageSafePointersAppModule)