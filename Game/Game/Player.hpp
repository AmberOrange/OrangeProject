#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Drawable.hpp"
#include "InputObserver.hpp"
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "InputHandler.hpp"
#include <queue>

class Player : public Drawable, public InputObserver
{
public:
	Player();
	~Player();

	void init();

	virtual void draw(Graphics &rGraphics);

	void update(const Uint32 delta);

private:
	struct InputBuffer
	{
		std::queue<Uint32> pressed;
		std::queue<Uint32> released;
		char isPressed = 0;
	};
	InputBuffer mInputBuffer[4];
	Uint32 mLastDelta;

	GLuint mVertexID;
	GLuint mVertexBuffer;
	glm::mat4 mWorldMatrix;

	Uint32 getInputTime(const Uint32 delta, int index);

	virtual void buttonPressed(Uint16 button, Uint32 timestamp);
	virtual void buttonReleased(Uint16 button, Uint32 timestamp);

};

#endif