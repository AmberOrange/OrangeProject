#include "InputHandler.hpp"


//Todo: Load keyboard binds, don't hardcode
SDL_Keycode keyboardBinds[COMMONBUTTON_COUNT] = {
	SDLK_z,
	SDLK_x,
	SDLK_c,
	SDLK_v,
	SDLK_UP,
	SDLK_DOWN,
	SDLK_LEFT,
	SDLK_RIGHT,
	SDLK_ESCAPE
};
std::vector<InputHandler::Subscribe> subscription;
InputHandler::CommonButtons keyToCommon(const SDL_Keycode &code);



void InputHandler::attach(InputObserver *observe, Uint16 subscribeButtons)
{
	subscription.push_back({
		observe,
		subscribeButtons
	});
}

void InputHandler::handleEvent(const SDL_KeyboardEvent &e)
{
	InputHandler::CommonButtons common = keyToCommon(e.keysym.sym);
	if (common == 0x0)
		return;

	for (unsigned int i = 0; i < subscription.size(); i++)
	{
		if ((subscription[i].subscribeButtons & common) == common)
		{
			if (e.state == SDL_PRESSED)
			{
				if(e.repeat == 0)
					subscription[i].observe->buttonPressed(common, e.timestamp);
			}
			else
				subscription[i].observe->buttonReleased(common, e.timestamp);
			break;
		}
	}
}

InputHandler::CommonButtons keyToCommon(const SDL_Keycode &code)
{
	unsigned int i = 0;
	bool found = false;
	for (; i < COMMONBUTTON_COUNT; i++)
	{
		if (code == keyboardBinds[i])
		{
			found = true;
			break;
		}
	}

	if (found)
		return (InputHandler::CommonButtons) ((0x01) << i);
	else
		return (InputHandler::CommonButtons) 0x0;
}