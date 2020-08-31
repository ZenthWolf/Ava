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

	Spawner(std::vector<std::unique_ptr<Enemy>>& nme,
			std::vector<std::unique_ptr<Behavior>>& bhv,
			std::vector<std::unique_ptr<Obstacle>>& obs);

	void AddEnemy(Creature body, Vec<float> pos, Vec<float> vel);
	void AddEnemy(Creature body, Creature mind, Vec<float> pos, Vec<float> vel);
	void AddObstacle(Vec<float> p0, Vec<float> p1);

	void ClearAll();
	void NewWave(int scenario);

private:
	void GiveBehavior(Enemy& spwn, Creature mind);

	std::vector<std::unique_ptr<Enemy>>& enemy;
	std::vector<std::unique_ptr<Behavior>>& behavior;
	std::vector<std::unique_ptr<Obstacle>>& obstacle;
};