#include "TextBox.h"

void TextBox::DrawFrame(Graphics& gfx) const
{
	Rect<int> Box = Rect<int>(50, 400, 750, 550);
	bev.DrawBevBorder(Box, 5, gfx);
	gfx.DrawRect(Box, Colors::DarkGray);
}
