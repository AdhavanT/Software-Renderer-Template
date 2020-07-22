#pragma once

#include "renderer.h"


//Sets a pixel of a Bitmap Buffer to a specidied color
inline bool Set_Pixel(Vec2<int32>& position, Vec3<uint8>& color, BitmapBuffer& buffer);

void Draw_Line(Vec2<int32> start_pos, Vec2<int32> end_pos, Vec3<uint8>& color, BitmapBuffer& buffer);

//void Draw_Circle(Vec2<int32> center, f32 radius, b8 filled, Vec3<uint8>& color, BitmapBuffer& buffer);
