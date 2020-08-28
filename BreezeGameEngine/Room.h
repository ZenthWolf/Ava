#pragma once
//Playground to identify needed interactions
//Eventual baseline for "Room" class, but don't take this shit seriously.

#include "Conflict.h"
#include "Obstacle.h"
#include "Input.h"

#include "Keyboard.h"
#include "Graphics.h"
#include <vector>
#include <memory>


class Room
{
public:
	Room(Character& Ava, int scenario, Keyboard& kbd);
	void Update(float dt);
	void Draw(Graphics& gfx);

private:
	void ReadInput();
	void CheckObstacles(); //Check entities are not colliding with obstacles
	void EnemyCollision(); //Check if Ava is in contact with an enemy
	void HitDetection(); //Detect Collision of attacks
	void Cull();

	Character& Ava; //Does Ava properly belong to the "Room" she is in? Or do rooms just "know" about her?
	Input AvaController;
	std::vector<std::unique_ptr<Enemy>> enemy; // Should have a list of enemies- ALL ENEMIES ARE REQUIRED TO DO ANYTHING STATED HERE, SO BASIS FOR SUBCLASS!
	std::vector<std::unique_ptr<Obstacle>> obstacle; // List of obstacles- which will eventually be a class like "ground" once was.

	Keyboard& kbd;
};