#include "MainThread.hpp"
//x #include <iostream>

MainThread::MainThread()
{
}

MainThread::~MainThread()
{
}

bool MainThread::init()
{
	if (!this->initVideo())
		return false;

	this->gameThread.init(&this->window);

	return true;
}

void MainThread::run()
{
	Uint32 frametime = 1000 / 120;
	Uint32 startTime;
	Uint32 elapsedTime;
	while (true)
	{
		startTime = SDL_GetTicks();
		if (EventHandler::DispatchEvents())
			break;

		gameThread.run(startTime);

		elapsedTime = (SDL_GetTicks()-startTime);
		if (elapsedTime < frametime)
			SDL_Delay(frametime - elapsedTime);
	}

	this->cleanup();
}

bool MainThread::initVideo()
{
	SDL_VideoInit(NULL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	this->window.init(
		"Orange Horizon",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_OPENGL);

	this->context = SDL_GL_CreateContext(this->window.getWindowHandler());

	//? What VSync setting should I have?
	SDL_GL_SetSwapInterval(0);
	//x std::cout << SDL_GL_GetSwapInterval() << std::endl;

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	//Todo glViewport should be in the graphic handling module
	glViewport(0, 0, this->window.getW(), this->window.getH());

	return true;
}

void MainThread::cleanup()
{
	SDL_GL_DeleteContext(this->context);
	this->window.destroy();
	SDL_VideoQuit();
}
