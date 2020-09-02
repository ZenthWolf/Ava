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
	std::string textLong = "Did you realize there is a limit to the amount of text you can write on a line before it goes out of the text box or even off the screen? I bet you didn't!\nYOU FOOL!";

	font.DrawText(text0, boxPos + boxBuffer, Colors::White, gfx);
	font.DrawText(text1, boxPos + boxBuffer + lineOffSet, Colors::White, gfx);

	int beginChar = 0;
	int nChar = 0;
	int LineLengthMax = lineEndPos - boxPos.X - boxBuffer.X;
	int LineLength = 0;
	int lineNum = 2;

	//OK, there definitely has to be a cooler way to do this...

	while ((beginChar + nChar) < textLong.size())
	{
		for (int c = 0; c < textLong.size() - beginChar; c++)
		{
			char thisChar = textLong[beginChar + c];

			if (thisChar == ' ')
			{
				nChar = c;
			}
			else if (thisChar == '\n')
			{
				nChar = c;
				break;
			}
			else if (c + 1 == textLong.size() - beginChar)
			{
				nChar = c + 1;
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

		font.DrawText(textLong.substr(beginChar, nChar), boxPos + boxBuffer + lineOffSet * lineNum - Vec<int>{0,300}, Colors::White, gfx);

		lineNum++;
		//assumes char after a space/newline is not a space, but we can deal with that later
		beginChar += nChar+1;
		nChar = 0;
		LineLength = 0;
	}
}
