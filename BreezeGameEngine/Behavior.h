/*
Behavior Controller for Enemies. Eventually, this will be made abstract, with this
as guideline for Blob enemies specifically.
*/

#pragma once

#include "Room.h"

class Behavior
{
public:
	Behavior(Enemy& self, Room& room);
	void Update(const float dt);
	bool Cull() const;

private:
	void MoveUpdate(const float dt);
	void AttackTimer(const float dt);
	void AimUpdate(const float dt);

	Enemy& self;
	Room& room;
	
	float atkTimer = 0.0f;
	float aimTimer = 0.0f;

	std::mt19937 rng;
};