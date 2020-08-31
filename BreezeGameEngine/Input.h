#pragma once

#include "Keyboard.h"
#include "Conflict.h"

class Input
{
public:
	Input(Character& ava, std::vector<std::unique_ptr<class Attack>>& atk, Keyboard& kbd);
	bool HasInput() const;
	void ReadInput();
private:
	Keyboard& kbd;
	Character& Ava;
	std::vector<std::unique_ptr<class Attack>>& attack;
};