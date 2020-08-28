#pragma once

#include "Keyboard.h"
#include "Conflict.h"

class Input
{
public:
	Input(Character& ava, Keyboard& kbd);
	bool HasInput() const;
	void ReadInput();
private:
	Keyboard& kbd;
	Character& Ava;
};