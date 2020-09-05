#pragma once

#include "Beveler.h"
#include "Font.h"

class TextBox
{
public:
	TextBox();
	void Draw(Graphics& gfx) const;
	void NextLine();
	bool IsFinished() const;
	void ProcessText(const std::string fulltext);

private:
	void DrawFrame(Graphics& gfx) const;
	void DrawTxt(Graphics& gfx) const;

	Beveler bev = Beveler(Colors::LightBlue);
	Font font = "Images//Fixedsys16x28.bmp";

	bool finished = false;
	std::vector<std::string> line;
	Vec<int> boxPos = { 50, 400 };
	Vec<int> boxBuffer = { 5, 5 };
	Vec<int> boxSize = { 700, 150 };
	Rect<int> Box;
	int boxBorderThickness = 5;
	Vec<int> lineOffSet;
	int curLine = 0;
	int lineBuffer = 2;
	int lineEndPos;
};