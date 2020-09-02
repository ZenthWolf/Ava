#include "TextBox.h"



TextBox::TextBox()
{
	Box = Rect<int>(boxPos, boxPos+boxSize);
	lineOffSet = { 0, font.GetHeight() + lineBuffer };
	lineEndPos = Box.X1 - boxBuffer.X - 20;
}

void TextBox::Draw(Graphics& gfx) const
{
	DrawFrame(gfx);
	DrawTxt(gfx);
}

void TextBox::DrawFrame(Graphics& gfx) const
{
	bev.DrawBevBorder(Box, boxBorderThickness, gfx);
	gfx.DrawRect(Box, Colors::DarkGray);
	gfx.DrawRect(Rect<int>(boxPos.X + boxBuffer.X, boxPos.Y + boxBuffer.Y, lineEndPos, boxPos.Y + boxSize.Y ), Colors::Green);
}

void TextBox::DrawTxt(Graphics& gfx) const
{
	std::string text0 = "The First Line of Text";
	std::string text1 = "The Next Line of Text";
	std::string textLong = "Did you realize there is a limit to the amount of text you can write on a line before it goes out of the text box or even off the screen? I bet you didn't!!!!!\nYOU FOOL!";

	font.DrawText(text0, boxPos + boxBuffer, Colors::White, gfx);
	font.DrawText(text1, boxPos + boxBuffer + lineOffSet, Colors::White, gfx);
	font.DrawText(std::string(textLong.begin()+4, textLong.begin()+7), boxPos + boxBuffer + lineOffSet*2, Colors::White, gfx);

	auto begin = textLong.begin();
	auto end = textLong.begin();
	int lineNum = 2;

	//OK, there definitely has to be a cooler way to do this...

	while (end != textLong.end())
	{
		int LineLengthMax = lineEndPos - boxPos.X - boxBuffer.X;
		int LineLength = 0;

		for (auto c = begin; c <= textLong.end(); ++c)
		{
			if (c == textLong.end())
			{
				end = c;
				break;
			}

			char thisChar = *c;

			if (thisChar == ' ')
			{
				end = c;
			}
			else if (thisChar == '\n')
			{
				end = c;
				break;
			}

			if (LineLength + font.CharWidth(thisChar) < LineLengthMax)
			{
				LineLength += font.CharWidth(thisChar);
			}
			else
			{
				break;
			}
		}

		font.DrawText(std::string(begin, end), boxPos + boxBuffer + lineOffSet * lineNum - Vec<int>{0,300}, Colors::White, gfx);

		lineNum++;
		if (end != textLong.end())
		{
			begin = end + 1;
			while (*begin == ' ' || *begin == '\n')
			{
				++begin;
			}
		}
	}
}
