#pragma once
//Playground to identify needed interactions
//Eventual baseline for "Room" class, but don't take this shit seriously.

#include "Conflict.h"
#include "Obstacle.h"

#include "Keyboard.h"
#include "Graphics.h"
#include <vector>
#include <memory>


class Room
{
public:
	Room(Character& Ava, Keyboard& kbd);
	void Update(float dt);
	void Draw(Graphics& gfx);
	void Cull();

	Character& Ava;
	std::vector<std::unique_ptr<Enemy>> enemy;
	std::vector<std::unique_ptr<Attack>> attack;
	std::vector<std::unique_ptr<Obstacle>> obstacle;

private:
	void EnemyCollision(); //Check if Ava is in contact with an enemy
	void HitDetection(); //Detect Collision of attacks

	Keyboard& kbd;
};