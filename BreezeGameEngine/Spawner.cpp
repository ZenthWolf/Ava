#include "Spawner.h"

Spawner::Spawner(Room& room, std::vector<std::unique_ptr<Behavior>>& bhv)
	:room(room), enemy(room.enemy), behavior(bhv), obstacle(room.obstacle), attack(room.attack)
{
}

void Spawner::AddEnemy(Creature body, Vec<float> pos, Vec<float> vel)
{
	AddEnemy(body, body, pos, vel);
}

void Spawner::AddEnemy(Creature body, Creature mind, Vec<float> pos, Vec<float> vel)
{
	switch (body)
	{
	case Creature::Blob:
	{
		enemy.push_back(
			std::make_unique<Enemy>(pos, vel)
		);

		int num = enemy.size() - 1;
		GiveBehavior(*enemy[num], mind);
		break;
	}
	}
}

void Spawner::AddObstacle(Vec<float> p0, Vec<float> p1)
{
	obstacle.push_back(
		std::make_unique<Obstacle>(p0, p1)
	);
}

void Spawner::ClearAll()
{
	behavior.clear();
	enemy.clear();
	attack.clear();
	obstacle.clear();
}

void Spawner::NewWave(int scenario)
{
	ClearAll();

	switch (scenario)
	{

	case 1:
	{
		// Enemies
		Vec<float> p = { 600.0f, 200.0f };
		Vec<float> v = { 0.0f, -70.0f };
		AddEnemy(Creature::Blob, p, v);

		//Obstacles
		p = { 560.0f, 540.0f };
		v = { 600.0f, 580.0f };
		AddObstacle(p, v);

		p = { 320.0f, 50.0f };
		v = { 360.0f, 90.0f };
		AddObstacle(p, v);
		break;
	}

	case 2:
	{
		//Enemies
		Vec<float> p = { 50.0f, 70.0f };
		Vec<float> v = { 100.0f, 0.0f };
		AddEnemy(Creature::Blob, p, v);

		p = { 300.0f, 450.0f };
		v = { 0.0f, 70.0f };
		AddEnemy(Creature::Blob, p, v);

		//Obstacles
		p = { 0.0f, 0.0f };
		v = { 20.0f, 600.0f };
		AddObstacle(p, v);
		
		p = { 0.0f, 0.0f };
		v = { 800.0f, 20.0f };
		AddObstacle(p, v);
		
		p = { 0.0f, 580.0f };
		v = { 800.0f, 600.0f };
		AddObstacle(p, v);

		p = { 780.0f, 0.0f };
		v = { 800.0f, 600.0f };
		AddObstacle(p, v);
	
		break;
	}

	case 3:
	{
		//Enemies
		Vec<float> p = { 680.0f, 70.0f };
		Vec<float> v = { 0.0f, -70.0f };
		AddEnemy(Creature::Blob, p, v);

		p = { 450.0f, 450.0f };
		v = { 0.0f, -170.0f };
		AddEnemy(Creature::Blob, p, v);

		p = { 590.0f, 270.0f };
		v = { 0.0f, 100.0f };
		AddEnemy(Creature::Blob, p, v);

		//Obstacles
		p = { 300.0f, 0.0f };
		v = { 350.0f, 600.0f };
		AddObstacle(p, v);

		p = { 0.0f, 0.0f };
		v = { 20.0f, 600.0f };
		AddObstacle(p, v);

		p = { 0.0f, 0.0f };
		v = { 800.0f, 20.0f };
		AddObstacle(p, v);

		p = { 0.0f, 580.0f };
		v = { 800.0f, 600.0f };
		AddObstacle(p, v);

		p = { 780.0f, 0.0f };
		v = { 800.0f, 600.0f };
		AddObstacle(p, v);

		break;
	}

	case 12:
	{
		Vec<float> center = { 400.0f,300.0f };
		double Pi = 3.1415926;

		//Enemies (Rad 7)
		Vec<float> p;
		Vec<float> v;

		for (int i = 0; i < 12; i++)
		{
			p = center + Vec<float>{ float(cos(2 * Pi * i/ 12)), float(-sin(2* Pi *i/ 12)) } * ( ((i + 8) % 12)*230/11 + 30 );
			v = (p-center).Norm() * (60 + ((i + 8) % 12)*5) * (-1 * (i % 2) + 1 * ((i + 1) % 2));
			AddEnemy(Creature::Blob, p, v);
		}

		//Obstacles
		p = { 380.0f, 280.0f };
		v = { 420.0f, 320.0f };
		AddObstacle(p, v);
		break;
	}

	default:
	{
		if (scenario % 12 == 0)
		{
			NewWave(12);
		}
		else
		{
			NewWave((scenario - 1) % 3 + 1);
		}
	}

	}
}

void Spawner::GiveBehavior(Enemy& spwn, Creature mind)
{
	switch (mind)
	{
	case Creature::Blob:
	{
		behavior.push_back(
			std::make_unique<Behavior>(spwn, room)
		);
		break;
	}
	}
}
