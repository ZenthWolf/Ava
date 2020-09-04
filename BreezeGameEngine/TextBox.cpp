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

std::vector<std::string> TextBox::ProcessText(const std::string fulltext) const
{
	std::vector<std::string> line;

	auto begin = fulltext.begin();
	auto end = fulltext.begin();

	while (end != fulltext.end())
	{
		int LineLengthMax = lineEndPos - boxPos.X - boxBuffer.X;
		int LineLength = 0;

		for (auto c = begin; c <= fulltext.end(); ++c)
		{
			if (c == fulltext.end())
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

		line.push_back(std::string(begin, end));

		if (end != fulltext.end())
		{
			begin = end + 1;
			while (*begin == ' ' || *begin == '\n')
			{
				++begin;
			}
		}
	}

	return line;
}

void TextBox::DrawFrame(Graphics& gfx) const
{
	bev.DrawBevBorder(Box, boxBorderThickness, gfx);
	gfx.DrawRect(Box, Colors::DarkGray);
	gfx.DrawRect(Rect<int>(boxPos.X + boxBuffer.X, boxPos.Y + boxBuffer.Y, lineEndPos, boxPos.Y + boxSize.Y ), Colors::Green);
}

void TextBox::DrawTxt(Graphics& gfx) const
{
	std::string text = "The First Line of Text\nThe Next Line of Text\nDid you realize there is a limit to the amount of text you can write on a line before it goes out of the text box or even off the screen? I bet you didn't!!!!!\nYOU FOOL!";
	std::vector<std::string> line = ProcessText(text);

	for (int i = 0; i < 3; i++)
	{
		font.DrawText(line[i], boxPos + boxBuffer + lineOffSet * i, Colors::White, gfx);
	}
}
