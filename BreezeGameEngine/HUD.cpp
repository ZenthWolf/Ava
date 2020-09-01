#include "HUD.h"
#include "Rect.h"

HUD::HUD(Character& ava, Room& room)
	:Ava(ava), room(room)
{
}

void HUD::Draw(const int wave, Graphics& gfx) const
{
	DrawWave(wave, gfx);
	DrawHealth(gfx);
	DrawArwCount(gfx);
	DrawNME(gfx);
}

void HUD::DrawWave(const int wave, Graphics& gfx) const
{
	std::string text = "Wave: ";
	text += std::to_string(wave);
	text += WaveName(wave);

	
	font.DrawText(text, Vec<int>(wavePosition), fontCol, gfx);
}

std::string HUD::WaveName(const int wave) const
{
	std::string name;
	switch (wave)
	{

	case 1:
	{
		name = "\nThe Lone Sentry";
		break;
	}
	case 2:
	{
		name = "\nTwin Guardians";
		break;
	}
	case 3:
	{
		name = "\nShooting Gallery";
		break;
	}
	case 12:
	{
		name = "\nTime to Die";
		break;
	}
	default:
	{
		if (wave % 12 == 0)
		{
			name = WaveName(12);
		}
		else
		{
			name = WaveName((wave - 1) % 3 + 1);
		}
	}

	}

	return name;
}

void HUD::DrawHealth(Graphics& gfx) const
{
	std::string text = "Life: ";

	font.DrawText(text, Vec<int>(healthPosition), fontCol, gfx);

	for (int i = 0; i < 3; i++)
	{
		bool fill = Ava.GetHealth() >= (i + 1);
		HPIcon(healthPosition + hpIconShift + hpIconSpace*i, fill, gfx);
	}
}

void HUD::HPIcon(const Vec<float> pos, bool fill, Graphics& gfx) const
{
	Rect<float> back = Rect<float>::FromCent(pos, 10, 10);
	Rect<float> frnt = Rect<float>::FromCent(pos, 7, 7);
	gfx.DrawRect(back, Colors::White);
	if (fill)
	{
		gfx.DrawRect(frnt, Colors::Red);
	}
	else
	{
		gfx.DrawRect(frnt, Colors::Black);
	}
}

void HUD::DrawArwCount(Graphics& gfx) const
{
	std::string text = "Arrows: \n  ";
	//text += std::to_string(room.enemy.size());
	text += "inf";
	font.DrawText(text, Vec<int>(arwPosition), fontCol, gfx);
	
}

void HUD::DrawNME(Graphics& gfx) const
{
	std::string text = "Enemies: \n  ";
	text += std::to_string(room.enemy.size());

	font.DrawText(text, Vec<int>(nmePosition), fontCol, gfx);
}
