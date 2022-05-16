#pragma once

#include "Math/Vector2Float.h"

struct Frame
{
	Frame()
		: myOrigin(0.0f)
		, mySize(0.0f)
		, myWorldSpace(0.0f)
		, myUVScale(0.0f)
		, myUVOffset(0.0f)
	{}

	Frame(Vector2Float anOrigin, Vector2Float aSize)
		: myOrigin(anOrigin)
		, mySize(aSize)
		, myWorldSpace(0.0f)
		, myUVScale(0.0f)
		, myUVOffset(0.0f)
	{}

	Vector2Float myOrigin;
	Vector2Float mySize;
	Vector2Float myWorldSpace;
	Vector2Float myUVScale;
	Vector2Float myUVOffset;
};