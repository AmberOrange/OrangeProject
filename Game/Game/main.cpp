#include <iostream>

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

#include "EventHandler.hpp"
#include "InputHandler.hpp"
#include "Graphics.hpp"
#include "Player.hpp"

const GLint WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	//SDL_GL_SetSwapInterval(1);


	SDL_Window *window = SDL_CreateWindow(
		"Orange Horizon",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_OPENGL);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to init GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, WIDTH, HEIGHT);

	//! TESTING GRAPHICS INIT
	Graphics graphics;
	try
	{
		graphics.init();
	}
	catch (const std::string e)
	{
		std::cout << e;
		std::cin.ignore();
		return EXIT_FAILURE;
	}

	//! TESTTING PLAYER
	Player player;

	//x SDL_Event windowEvent;

	Uint32 lastDelta = SDL_GetTicks();

	while (true)
	{
		/*while ((SDL_GetTicks() - lastDelta) < (1000 / 60))
		{
			SDL_PumpEvents();
		}
		lastDelta = SDL_GetTicks();*/

		if (EventHandler::DispatchEvents())
			break;

		player.update(SDL_GetTicks());

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		graphics.useProgram(0);
		player.draw(graphics);

		SDL_GL_SwapWindow(window);
		
		SDL_Delay(1000 / 60);
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}