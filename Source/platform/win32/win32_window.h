#pragma once
#include <Windows.h>
#include "frameloop.h"

struct Win32_BitmapBuffer
{
	BITMAPINFO info;
	BitmapBuffer bitmap_buffer;
};

struct WindowDimensions 
{
	uint32 width;
	uint32 height;
};