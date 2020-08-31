#pragma once

#include "Room.h"

class Collider
{
public:
	Collider() = default;
	void StaticCollider(Room& room) const;
	void AttackCollider(Room& room) const;
private:

};