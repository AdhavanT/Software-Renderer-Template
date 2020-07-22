#include "frameloop.h"
#include <renderer/render_methods.h>

void CoreLoop(BitmapBuffer &bitmap_buffer,f32 delta_time)
{
	Vec3<uint8> color = { 0,255,0 };
	Vec2<int32> center = { (int32)bitmap_buffer.width / 2,(int32)bitmap_buffer.height / 2 };
	Vec2<int32> top = { center.x + 100, center.y };

	Draw_Line(center, top, color, bitmap_buffer);
}
