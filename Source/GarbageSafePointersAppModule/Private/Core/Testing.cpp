#include "GarbageSafePointersAppModule/Public/Core/Testing.h"

const FFilePath TestPaths[] = { TEXT("D:\\Game Projects\\TestProject\\Source\\TestFolderA")
							  , TEXT("D:\\Game Projects\\TestProject\\Source\\TestFolderB")
							  , TEXT("D:\\Game Projects\\TestProject\\Source\\TestFolderC")
							  , TEXT("D:\\Game Projects\\TestProject\\Source\\TestFolderD")
							  , TEXT("D:\\Game Projects\\TestProject\\Source\\TestFolderE")
							  , TEXT("D:\\Game Projects\\TestProject\\Source\\TestFolderF")
							  , TEXT("D:\\Game Projects\\TestProject\\Source\\TestFolderF\\NestedTestFolderA")
							  , TEXT("D:\\Game Projects\\TestProject\\Source\\TestFolderF\\NestedTestFolderB")
							  , TEXT("D:\\Game Projects\\TestProject\\Source\\TestFolderF\\NestedTestFolderC")
							  , TEXT("D:\\Game Projects\\TestProject\\Source\\TestFolderF\\NestedTestFolderD")
							  , TEXT("D:\\Game Projects\\TestProject\\Source\\TestFolderF\\NestedTestFolderE") };


const FString TestFileNames[] = { TEXT("TestFileA.h")
								, TEXT("TestFileB.h")
								, TEXT("TestFileC.h")
								, TEXT("TestFileD.h")
								, TEXT("TestFileE.h")
								, TEXT("TestFileF.h")
								, TEXT("TestFileD.h")
								, TEXT("TestFileG.h")
								, TEXT("TestFileH.h") };

const FString TestTypes[] = { TEXT("UObject")
							, TEXT("AActor")
							, TEXT("ACharacter")
							, TEXT("APawn")
							, TEXT("ULevelSequenceActor")
							, TEXT("UActorComponent")
							, TEXT("AStaticMeshActor")
							, TEXT("UProperty")
							, TEXT("UClass")
							, TEXT("UAssetUserData")
							, TEXT("UDataAsset") };

constexpr uint32 TestPathNum	 = UE_ARRAY_COUNT(TestPaths);
constexpr uint32 TestFileNameNum = UE_ARRAY_COUNT(TestFileNames);
constexpr uint32 TestTypeNum	 = UE_ARRAY_COUNT(TestTypes);

static_assert(TestPathNum);
static_assert(TestFileNameNum);
static_assert(TestTypeNum);

FStructuredPointerQueryResult ConstructTestResult_General()
{
	constexpr uint32 Seed = 16;
	
	constexpr uint32 TestPathC = StableRandRange(0u, TestPathNum - 1, Seed);
	constexpr uint32 TestFileC = StableRandRange(0u, TestFileNameNum - 1, Seed + 1);
	constexpr uint32 TestTypeC = StableRandRange(0u, TestTypeNum - 1, Seed + 2);

	FStructuredPointerQueryResult QueryResult;

	QueryResult.NumberOfQueriedFiles = TestPathC * TestFileC;
	QueryResult.NumberOfSkippedFiles = 0u;
	QueryResult.NumberOfFoundUnsafePointers = TestPathC * TestFileC * TestTypeC;

	QueryResult.QueryResults.Reserve(TestPathC);

	
	for (uint32 Index = 0u; Index < TestPathC * TestFileC; ++Index)
	{
		FFileQueryResult& FileQuery = QueryResult.QueryResults.Add_GetRef(FFileQueryResult());

		const uint32 PathIndex = Index / TestPathC;
		const uint32 FileIndex = Index % TestPathC;
		
		FileQuery.FilePath.FilePath = FString::Printf(TEXT("%s\\%s"),*TestPaths[PathIndex].FilePath, *TestFileNames[FileIndex]);
		FileQuery.QueryID = Index;
		FileQuery.Fragments.Reserve(TestTypeC);

		uint32 FragmentLineIndex = 1u;
		
		for (uint32 FragmentIndex = 0; FragmentIndex < TestTypeC; ++FragmentIndex)
		{
			FQueryResultFragment& Fragment = FileQuery.Fragments.Add_GetRef(FQueryResultFragment());

			Fragment.Type = TestTypes[FragmentIndex];
			Fragment.Line = (FragmentLineIndex += FMath::RandRange(1, 10));
			Fragment.ParentQueryID = FileQuery.QueryID;
		}
	}
	
	return QueryResult;
}
