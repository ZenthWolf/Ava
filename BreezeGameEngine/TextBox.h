#pragma once

#include "Beveler.h"
#include "Font.h"

class TextBox
{
public:
	TextBox();
	void Draw(Graphics& gfx) const;

private:
	std::vector<std::string> ProcessText(const std::string fulltext) const;
	void DrawFrame(Graphics& gfx) const;
	void DrawTxt(Graphics& gfx) const;

	Beveler bev = Beveler(Colors::LightBlue);
	Font font = "Images//Fixedsys16x28.bmp";

	Vec<int> boxPos = { 50, 400 };
	Vec<int> boxBuffer = { 5, 5 };
	Vec<int> boxSize = { 700, 150 };
	Rect<int> Box;
	int boxBorderThickness = 5;
	Vec<int> lineOffSet;
	int lineBuffer = 2;
	int lineEndPos;
};