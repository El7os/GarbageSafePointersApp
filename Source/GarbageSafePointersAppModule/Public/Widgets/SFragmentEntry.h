#pragma once

struct FQueryResultFragment;


class SFragmentEntry : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SFragmentEntry)
		: _Fragment(nullptr)
	{
	}
	SLATE_ARGUMENT(FQueryResultFragment*, Fragment)
	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs);
};