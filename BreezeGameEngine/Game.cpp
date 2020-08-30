/***************************************************************************/
/***               Temper Tech DirectX Framework V 1.0.0                 ***/
/*** Game.cpp                                                            ***/
/*** Copyright for all time (if your law disagrees, it can suck it)      ***/
/***                                                                     ***/
/*** Part of the Temper DirectX Framework                                ***/
/***                                                                     ***/
/*** Proprietary Software, do not read.                                  ***/
/*** You cannot use it, look at it, or have it on your computer,         ***/
/*** unless you are a working member of Temper Tech                      ***/
/***                                                                     ***/
/*** If you need help, go fuck yourself.                                 ***/
/***************************************************************************/

#include "MainWindow.h"
#include "Game.h"
#include<iostream>


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(std::random_device()())
{

}

void Game::Play()
{
	gfx.BeginFrame();

	int iter = 0;

	float elapseTime = ft.Mark();

	while (elapseTime > 0.0f)
	{
		float dt = std::min(0.0025f, elapseTime);
		UpdateModel(dt);
		elapseTime -= dt;

		iter++;
	}

	ComposeFrame(iter);
	gfx.EndFrame();
}


void Game::UpdateModel(float dt)
{
	room.Update(dt);
	collider.StaticCollider(room);
}


void Game::ComposeFrame(int iter)
{
	room.Draw(gfx);

	std::string text = "It's alone to be dangerous. . . \nTake-a a-dis!\nNumber Iterations: ";
	text += std::to_string(iter);
	font.DrawText(text, { 100, 175 }, Color(255, 255, 255), gfx);
}
