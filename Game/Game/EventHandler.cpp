#include "EventHandler.hpp"
#include "InputHandler.hpp"
#include <SDL.h>

bool EventHandler::DispatchEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			InputHandler::handleEvent(e.key);
			break;
		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERBUTTONUP:
			//todo InputHandler::handleEvent(e.cbutton);
			break;
		case SDL_QUIT:
			return true;
			break;
		}
	}
	return false;
}
