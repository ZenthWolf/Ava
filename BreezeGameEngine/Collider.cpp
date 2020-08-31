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

void Collider::AttackCollider(Room& room) const
{
	for (auto& atk : room.attack)
	{
		Rect<float> atkBox = atk->GetCollBox();

		if (atk->GetAllegiance() == Entity::Allegiance::Enemy)
		{
			if ( atkBox.CollWith( room.Ava.GetCollBox() ) )
			{
				room.Ava.OnHit(*atk);
			}
		}

		else if (atk->GetAllegiance() == Entity::Allegiance::Ava)
		{
			for (auto& nme : room.enemy)
			{
				if (atkBox.CollWith(nme->GetCollBox()))
				{
					nme->OnHit(*atk);
				}
			}
		}
	}
}
