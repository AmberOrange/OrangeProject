#ifndef INPUTOBSERVER_HPP
#define INPUTOBSERVER_HPP
#include <SDL_stdinc.h>

class InputObserver
{
public:
	virtual void buttonPressed(Uint16 button, Uint32 timestamp) = 0;
	virtual void buttonReleased(Uint16 button, Uint32 timestamp) = 0;
};

#endif