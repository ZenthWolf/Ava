#include "Room.h"

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
		if (e.GetCode() == ' ' || e.GetCode() == 'Z' || abs(e.GetCode() - 37) <= 3) // Arrow Keys are 37-40
															  // This passes 34 -> 40... oops?
		{
			Ava.Input(e);
		}
	}
}

void Room::Update(float dt)
{
	ReadInput();

	// Inform dynamic objects that it is time to update!
	// Characters and Enemies should update their attacks at this time.
	Ava.Update(dt);
	for (int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->Update(dt);
	}

	//Do the collisiony type stuff
	CheckObstacles();
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
		enemy[i]->Draw2(gfx);
	}
}

void Room::CheckObstacles()
{
	for (int i = 0; i < obstacle.size(); i++)
	{
		//STATIC COLLISION

		Rect<float> staticBox = obstacle[i]->GetCollBox();

		//Check Ava/Obstacle Collision
		if ( staticBox.CollWith( Ava.GetCollBox() ) )
		{
			Ava.PushBox( staticBox ); // A function which replaces Ava to end collision
		}

		//Check Enemy/Obstacle Collision
		for (int j = 0; j < enemy.size(); j++)
		{
			Rect<float> enemyBox = enemy[j]->GetCollBox();

			if ( staticBox.CollWith(enemyBox) )
			{
				enemy[j]->PushBox( staticBox ); // A function which replaces Enemy to end collision- may also alter behavior
			}
		}
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
				Combat.AttackOn(Ava.GetAttack(i), *enemy[j]);
				//enemy[j]->OnHit(Ava, i);
			}
		}
	}
}
