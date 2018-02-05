#include "Window.hpp"

Window::Window()
{
}

Window::~Window()
{
}

void Window::init(
	const char *title,
	int x,
	int y,
	int w,
	int h,
	Uint32 flags)
{
	this->windowHandler = SDL_CreateWindow(
		title,
		x,
		y,
		w,
		h,
		SDL_WINDOW_OPENGL);

	this->dimensions[0] = x;
	this->dimensions[1] = y;
	this->dimensions[2] = w;
	this->dimensions[3] = h;
}

void Window::destroy()
{
	SDL_DestroyWindow(this->windowHandler);
}

SDL_Window *Window::getWindowHandler() const
{
	return this->windowHandler;
}

int Window::getX() const
{
	return this->dimensions[0];
}

int Window::getY() const
{
	return this->dimensions[1];
}

int Window::getW() const
{
	return this->dimensions[2];
}

int Window::getH() const
{
	return this->dimensions[3];
}
