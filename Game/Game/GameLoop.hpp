#ifndef GAMETHREAD_HPP
#define GAMETHREAD_HPP

#include <SDL_timer.h>

#include "Player.hpp"
#include "Graphics.hpp"
#include "Window.hpp"
#include "Compute.hpp"

class GameLoop
{
public:
	GameLoop();
	~GameLoop();

	void init(Window *window);
	void run(Uint32 startTime);
private:
	Window *pWindow;
	Player mPlayer;
	Graphics mGraphics;
	Compute mCompute;
};

#endif