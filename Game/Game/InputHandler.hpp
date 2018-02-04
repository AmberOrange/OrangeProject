#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#define COMMONBUTTON_COUNT 9
//#include <cstdint>
#include <SDL_stdinc.h>
#include <SDL_events.h>
#include <vector>
#include "InputObserver.hpp"

namespace InputHandler {
	enum CommonButtons : Uint16
	{
		A = 0x0001,
		B = 0x0002,
		C = 0x0004,
		D = 0x0008,
		UP = 0x0010,
		DOWN = 0x0020,
		LEFT = 0x0040,
		RIGHT = 0x0080,
		ESCAPE = 0x0100
	};
	/*struct ButtonEvent
	{
		CommonButtons button;
		Uint32 timestamp;
	};*/
	/*struct Subscribe
	{
		void *id;
		void(*pressed)(ButtonEvent&);
		void(*released)(ButtonEvent&);
		Uint16 subscribeButtons;
	};*/
	struct Subscribe
	{
		InputObserver *observe;
		Uint16 subscribeButtons;
	};

	void attach(InputObserver *observe, Uint16 subscribeButtons);
	void handleEvent(const SDL_KeyboardEvent &e);
	//todo void handleEvent(const SDL_ControllerButtonEvent &e);

};

#endif