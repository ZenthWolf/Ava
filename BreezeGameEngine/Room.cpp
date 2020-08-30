#include "Room.h"
#include <algorithm>

Room::Room(Character& Ava, int scenario, Keyboard& kbd)
	:Ava(Ava), kbd(kbd)
{
	if (scenario == 0)
	{
		Vec<float> p = { 600.0f, 200.0f };
		Vec<float> v = { 0.0f, -70.0f };

		enemy.push_back(
			std::make_unique<Enemy>(p, v)
		);

		obstacle.push_back(
			std::make_unique<Obstacle>(Vec<float>(560.0f, 540.0f), Vec<float>(600.0f, 580.0f))
		);
		obstacle.push_back(
			std::make_unique<Obstacle>(Vec<float>(320.0f, 50.0f), Vec<float>(360.0f, 90.0f))
		);
	}
}

// The purpose here is to throw out irrelevant keys without feeding them to any entities.
void Room::ReadInput() const
{
	while (!kbd.KeyIsEmpty())
	{
		const Keyboard::Event e = kbd.ReadKey();
		if (e.GetCode() == ' ' || e.GetCode() == 'Z' || e.GetCode() == 'X' || abs(e.GetCode() - 37) <= 3) // Arrow Keys are 37-40
															  // This passes 34 -> 40... oops?
		{
			Ava.Input(e);
		}
	}
}

void Room::Update(float dt)
{
	if (kbd.KeyIsPressed('W'))
	{
		auto e = kbd.ReadKey();
		bool ono = true;
	}

	ReadInput();

	// Inform dynamic objects that it is time to update!
	// Characters and Enemies should update their attacks at this time.
	Ava.Update(dt);

	//Do the collisiony type stuff
	HitDetection();      //Active hits have preference over passive hits
//	EnemyCollision();
}

void Room::Draw(Graphics& gfx)
{
	for (int i = 0; i < obstacle.size(); i++)
	{
		obstacle[i]->Draw(gfx);
	}
	Ava.Draw(gfx);
	for (int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->Draw(gfx);
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

void Room::HitDetection()
{
	for (int i = 0; i < Ava.GetAttackNum(); i++)
	{
		for (int j = 0; j < enemy.size(); j++)
		{
			if (Ava.GetAttackBox(i).CollWith(enemy[j]->GetCollBox()))
			{
				enemy[j]->OnHit(Ava.GetAttack(i));
			}
		}
	}
}

void Room::Cull()
{
	enemy.erase(std::remove_if(enemy.begin(), enemy.end(), 
		[](std::unique_ptr<Enemy>& i) {return i->Cull(); }
		), enemy.end());
}