#include "Collider.h"

void Collider::StaticCollider(Room& room) const
{
	auto& obstacle = room.obstacle;
	auto& enemy = room.enemy;
	auto& Ava = room.Ava;

	for (auto& obs : obstacle)
	{
		Rect<float> staticBox = obs->GetCollBox();

		if (staticBox.CollWith(Ava.GetCollBox()))
		{
			Ava.PushBox(staticBox);
		}

		for (auto& nme : enemy)
		{
			Rect<float> enemyBox = nme->GetCollBox();

			if (staticBox.CollWith(enemyBox))
			{
				nme->PushBox(staticBox);
			}
		}
	}
}
