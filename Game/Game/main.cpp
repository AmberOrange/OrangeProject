#include <iostream>

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

#include "EventHandler.hpp"
#include "InputHandler.hpp"

const GLint WIDTH = 800, HEIGHT = 600;

void test_pressed(InputHandler::ButtonEvent &e)
{
	std::cout << "Button nr: " << e.button
		<< " pressed at timestamp: " << e.timestamp << std::endl;
}

void test_released(InputHandler::ButtonEvent &e)
{
	std::cout << "Button nr: " << e.button
		<< " released at timestamp: " << e.timestamp << std::endl;
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	//x SDL_DisplayMode DM;
	//x SDL_GetCurrentDisplayMode(0, &DM);

	SDL_Window *window = SDL_CreateWindow(
		"Orange Horizon",
		//x DM.w / 2 - WIDTH / 2,
		//x DM.h / 2 - HEIGHT / 2,
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

	//! TESTING OF INPUT
	InputHandler::attach({
		nullptr,
		test_pressed,
		test_released,
		InputHandler::A | 
		InputHandler::B
	});

	SDL_Event windowEvent;

	while (true)
	{
		/*if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
			{
				break;
			}
		}*/

		if (EventHandler::DispatchEvents())
			break;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}