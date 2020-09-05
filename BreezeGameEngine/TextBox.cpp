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

void TextBox::ProcessText(const std::string fulltext)
{
	finished = false;

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
}

void TextBox::DrawFrame(Graphics& gfx) const
{
	bev.DrawBevBorder(Box, boxBorderThickness, gfx);
	gfx.DrawRect(Box, Colors::DarkGray);
	gfx.DrawRect(Rect<int>(boxPos.X + boxBuffer.X, boxPos.Y + boxBuffer.Y, lineEndPos, boxPos.Y + boxSize.Y ), Colors::Green);
}

void TextBox::DrawTxt(Graphics& gfx) const
{
	for (int i = curLine; i < min(curLine+3, line.size()); i++)
	{
		font.DrawText(line[i], boxPos + boxBuffer + lineOffSet * (i-curLine), Colors::White, gfx);
	}
}

void TextBox::NextLine()
{
	if (curLine + 2 < line.size())
	{
		curLine = min(curLine + 2,line.size() - 1);
	}
	else
	{
		finished = true;
	}
}

bool TextBox::IsFinished() const
{
	return finished;
}
