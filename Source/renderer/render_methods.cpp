#include "render_methods.h"

//Sets a pixel of a Bitmap Buffer to a specidied color
inline bool Set_Pixel(Vec2<int32>& position, Vec3<uint8>& color, BitmapBuffer& buffer)
{
	if (!(((position.x <= buffer.width) || (position.x >= 0)) || ((position.y <= buffer.height) || (position.y >= 0))))
	{
		ASSERT(false);
		return false;
	}
	uint32* pixel = (uint32*)buffer.buffer_memory;
	pixel += position.y * buffer.width + position.x;
	*pixel = *(uint32*)&color.raw[0];
	return true;
}

void Draw_Line(Vec2<int32> start_pos, Vec2<int32> end_pos, Vec3<uint8>& color, BitmapBuffer& buffer)
{
	//Using Set_Pixel
	if (start_pos.x > end_pos.x)
	{
		myops::swap(start_pos, end_pos);
	}
	f32 slope = (end_pos.y - start_pos.y) / (f32)(end_pos.x - start_pos.x);
	f32 pos_y = (f32)start_pos.y;
	Vec2<int32> pos = {};
	for (int32 x = start_pos.x; x < end_pos.x; x++)
	{
		pos_y += slope;
		pos = { x, (int32)pos_y };
		Set_Pixel(pos, color, buffer);
	}
}


//TODO: find a new method to render circles efficiently.

//void Draw_Circle(Vec2<int32> center, f32 radius, b8 filled, Vec3<uint8>& color, BitmapBuffer& buffer)
//{
//	ASSERT(radius > 0);
//	
//	int32 radius_sqred = (int32)myops::sqr(radius);
//	
//	int32 int_radius = (int32)radius;
//
//	Vec2<int32> draw_pos_offset;
//	Vec2<int32> draw_pos;
//	draw_pos_offset = { (int32)radius, 0};
//	
//	while (draw_pos_offset.y <= int_radius)
//	{
//		if (draw_pos_offset.mag2() - radius_sqred > 0)
//		{
//			draw_pos_offset.x--;
//		}
//		draw_pos = { center.x + draw_pos_offset.x, center.y + draw_pos_offset.y };
//		Set_Pixel(draw_pos, color, buffer);
//		draw_pos = { center.x - draw_pos_offset.y, center.y - draw_pos_offset.x };
//		Set_Pixel(draw_pos, color, buffer);
//
//		draw_pos_offset.y++;
//	}
//	
//}