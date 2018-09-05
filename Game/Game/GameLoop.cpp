#include "GameLoop.hpp"

GameLoop::GameLoop()
{
}

GameLoop::~GameLoop()
{
}

void GameLoop::init(Window *window)
{
	this->pWindow = window;
	this->mGraphics.init();
	this->mCompute.Init();
	this->mPlayer.init();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void GameLoop::run(Uint32 startTime)
{
	this->mPlayer.update(SDL_GetTicks());

	glClear(GL_COLOR_BUFFER_BIT);
	this->mGraphics.useProgram(0);

	this->mPlayer.draw(this->mGraphics);

	SDL_GL_SwapWindow(this->pWindow->getWindowHandler());

}