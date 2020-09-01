#pragma once

#include "Beveler.h"
#include "Graphics.h"

class TextBox
{
public:
	void DrawFrame(Graphics& gfx) const;
private:
	Beveler bev = Beveler(Colors::LightBlue);
};