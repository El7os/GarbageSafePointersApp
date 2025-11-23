#pragma once

struct FQueryResultFragment
{
public:

	FQueryResultFragment()
		: Type(FString())
		, Line(0)
		, ParentQueryID(INDEX_NONE)
	
	{
	}

	FQueryResultFragment(FQueryResultFragment&& Fragment)
		: Type(MoveTemp(Fragment.Type))
		, Line(Fragment.Line)
		, ParentQueryID(Fragment.ParentQueryID)
	{
		Fragment.Type = FString();
	}
	
	FORCEINLINE bool IsValid() const
	{
		return ParentQueryID != INDEX_NONE;
	}

public:
	
	// Type or the detected unsafe pointer
	FString Type;

	// Actual line number of the detected unsafe pointer inside the file.
	uint32 Line;

	// Query ID of the FileQueryResult that contains this fragment
	int32 ParentQueryID;
};

struct FFileQueryResult
{
	FFilePath FilePath;

	// Array of individual query results.
	TArray<FQueryResultFragment> Fragments;

	int32 QueryID;
};


struct FStructuredPointerQueryResult
{
	TArray<FFileQueryResult> QueryResults;	

	// The raw number of queried files, including skipped ones.
	uint32 NumberOfQueriedFiles;

	// The total number of skipped files.
	uint32 NumberOfSkippedFiles;

	// The number of detected pointers that is proven to be unsafe.
	uint32 NumberOfFoundUnsafePointers;
};