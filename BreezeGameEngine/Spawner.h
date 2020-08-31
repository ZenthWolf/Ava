#pragma once

#include "Conflict.h"
#include "Behavior.h"
#include "Obstacle.h"


class Spawner
{
public:
	enum class Creature
	{
		Blob
	};

	Spawner(Room& room, std::vector<std::unique_ptr<Behavior>>& bhv);

	void AddEnemy(Creature body, Vec<float> pos, Vec<float> vel);
	void AddEnemy(Creature body, Creature mind, Vec<float> pos, Vec<float> vel);
	void AddObstacle(Vec<float> p0, Vec<float> p1);

	void ClearAll();
	void NewWave(int scenario);

private:
	void GiveBehavior(Enemy& spwn, Creature mind);

	Room& room;
	std::vector<std::unique_ptr<Enemy>>& enemy;
	std::vector<std::unique_ptr<Behavior>>& behavior;
	std::vector<std::unique_ptr<Attack>>& attack;
	std::vector<std::unique_ptr<Obstacle>>& obstacle;
};