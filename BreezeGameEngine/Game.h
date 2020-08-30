/***************************************************************************/
/***               Temper Tech DirectX Framework V 1.0.0                 ***/
/*** Game.h                                                              ***/
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include <chrono>
#include "Sound.h"
#include "Font.h"
#include <random>

//#include "Conflict.h"
#include "Input.h"
#include "Room.h"
#include "Behavior.h"
#include "Collider.h"


class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Play();
private:
	void ComposeFrame(int iter);
	void UpdateModel(float dt);
	void Cull();

	/********************************/
	/*  User Functions              */
	/********************************/
	enum class GameState
	{
		Title,
		Play
	};

private:
	MainWindow& wnd;
	Graphics gfx;
	FrameTimer ft;
	/********************************/
	/*  User Variables              */
	/********************************/
	std::mt19937 rng;
	GameState gameState = GameState::Play;

	Character ava = Character({ 100.0f, 100.0f }, wnd.kbd);
	Input avaController;
	std::vector<std::unique_ptr<Behavior>> behavior;

	Room room = Room(ava, 0, wnd.kbd);
	Collider collider = Collider();
	Font font = "Images//Fixedsys16x28.bmp";
};
