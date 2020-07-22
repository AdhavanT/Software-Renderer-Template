#pragma once
#include <common headers/types.h>

struct BitmapBuffer
{
	void* buffer_memory;
	uint32 bytes_per_pixel;
	uint32 width;
	uint32 height;

	inline uint32 size() { return (bytes_per_pixel * width * height); };
};
