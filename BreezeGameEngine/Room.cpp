#include "Room.h"
#include <algorithm>

Room::Room(Character& Ava, Keyboard& kbd)
	:Ava(Ava), kbd(kbd)
{
}

void Room::Update(float dt)
{
	// Inform dynamic objects that it is time to update!
	// Characters and Enemies should update their attacks at this time.
	Ava.Update(dt);

}

void Room::Draw(Graphics& gfx)
{
	for (auto& o : obstacle)
	{
		o->Draw(gfx);
	}
	Ava.Draw(gfx);
	for (auto& e : enemy)
	{
		e->Draw(gfx);
	}
	for (auto& a : attack)
	{
		a->Draw(gfx);
	}
}

/*
void Room::EnemyCollision()
{
	//Check Ava/Enemy Collision
	Rect<float> avaBox = Ava.GetCollBox();

	for (int i = 0; i < Enemy.size(); i++)
	{
		Rect<float> enemyBox = Enemy[i].GetCollBox();
		if (IsColliding(avaBox, enemyBox ))
		{
			// Ava has a response- gets hit, flashes, is pushed away, etc.
			// Enemy may have a response- animation/sound effect, health gain, tactics change
			// Details of hit may be enemy dependent. The ENEMY should handle the process since it is the most unpredictable piece!

			Enemy[i].Contact(Ava);
			break; // Only one may hit

			//
			//	Note: The quality of this hit detection scheme will be interesting with multiple enemies. It may make for eratic recoiling by Ava
			//	and become unintentionally frustrating. Two possible tunes: Easy- the *closest* contact matters, not the arbitrary first; or Hard-
			//	an entirely new scheme of hit detection which scans the whole screen more objectively to find a "reasonable" direction
			//
		}
	}
}
*/

void Room::Cull()
{
	enemy.erase(std::remove_if(enemy.begin(), enemy.end(), 
		[](std::unique_ptr<Enemy>& i) {return i->Cull(); }
		), enemy.end());

	attack.erase(std::remove_if(attack.begin(), attack.end(),
		[](std::unique_ptr<Attack>& i) {return i->Cull(); }
	), attack.end());
}