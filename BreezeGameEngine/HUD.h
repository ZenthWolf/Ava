#pragma once

#include "Room.h"
#include "Font.h"

class HUD
{
public:
	HUD(Character& ava, Room& room);
	void Draw(const int wave, Graphics& gfx) const;

private:
	void DrawWave(const int wave, Graphics& gfx) const;
	std::string WaveName(const int wave) const;
	void DrawHealth(const int hp, Graphics& gfx) const;
	void HPIcon(const Vec<float> pos, bool fill, Graphics& gfx) const;

	Font font = "Images//Fixedsys16x28.bmp";
	Color fontCol = Color(255, 255, 255);

	Character& Ava;
	Room& room;
	Vec<float> wavePosition = { 0.0f, 0.0f };
	Vec<float> healthPosition = { 650.0f, 0.0f };
	Vec<float> hpIconShift = { 15.0f, 40.0f };
	Vec<float> hpIconSpace = { 25.0f, 0.0f };


};