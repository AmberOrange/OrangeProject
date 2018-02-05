#ifndef MAINTHREAD_HPP
#define MAINTHREAD_HPP

#include "Window.hpp"

#include <GL\glew.h>
#include <SDL_video.h>

#include "EventHandler.hpp"
#include "GameLoop.hpp"

class MainThread
{
public:
	MainThread();
	~MainThread();

	bool init();
	void run();

private:
	Window window;
	SDL_GLContext context;
	GameLoop gameThread;

	bool initVideo();
	void cleanup();
};

#endif