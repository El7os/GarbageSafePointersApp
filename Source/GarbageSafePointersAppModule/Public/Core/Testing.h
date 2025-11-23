#pragma once

#include "CoreTypes.h"

extern const FFilePath TestPaths[];
extern const FString TestFileNames[];
extern const FString TestTypes[];

constexpr uint32 StableRandRange(uint32 RangeMin, uint32 RangeMax, uint32 Seed)
{
	return RangeMin + (((1103515245u * Seed + 12345u) % 2147483648u) % (RangeMax - RangeMin + 1));
}

FStructuredPointerQueryResult ConstructTestResult_General();