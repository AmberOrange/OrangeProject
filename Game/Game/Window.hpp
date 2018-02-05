#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SDL_video.h>

class Window
{
public:
	Window();
	~Window();

	void init(
		const char* title,
		int x,
		int y,
		int w,
		int h,
		Uint32 flags);
	void destroy();

	SDL_Window *getWindowHandler() const;
	int getX() const;
	int getY() const;
	int getW() const;
	int getH() const;
private:
	SDL_Window *windowHandler;
	int dimensions[4];

};

#endif