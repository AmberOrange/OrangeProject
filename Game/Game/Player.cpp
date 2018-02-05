#include "Player.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

Player::Player()
{
}

Player::~Player()
{
}

void Player::init()
{
	glGenVertexArrays(1, &this->mVertexID);
	glBindVertexArray(this->mVertexID);
	const GLfloat data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	glGenBuffers(1, &this->mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	this->mWorldMatrix = glm::scale(
		this->mWorldMatrix,
		glm::vec3(0.1f, 0.2f, 0.5f));

	InputHandler::attach(
		this,
		InputHandler::UP |
		InputHandler::DOWN |
		InputHandler::LEFT |
		InputHandler::RIGHT);

	this->mLastDelta = 0;
}

void Player::draw(Graphics &rGraphics)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->mVertexBuffer);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		nullptr
	);
	glProgramUniformMatrix4fv(
		rGraphics.getCurrentProgram(),
		rGraphics.getWorldLocation(),
		1,
		GL_FALSE,
		glm::value_ptr(this->mWorldMatrix)
	);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

}

void Player::update(const Uint32 delta)
{
	glm::vec3 move;
	move.y += this->getInputTime(delta, 0);
	move.y -= this->getInputTime(delta, 1);
	move.x -= this->getInputTime(delta, 2);
	move.x += this->getInputTime(delta, 3);
	move /= 100.f;
	this->mLastDelta = delta;

	this->mWorldMatrix = glm::translate(this->mWorldMatrix, move);
}

Uint32 Player::getInputTime(const Uint32 delta, int index)
{
	Uint32 total = 0;
	Uint32 lastDelta = this->mLastDelta;
	Uint32 pop = 0;
	InputBuffer &buffer = this->mInputBuffer[index];

	//Todo This may end up in an infinite loop, got to fix
	while (!buffer.pressed.empty() || !buffer.released.empty())
	{
		if (buffer.isPressed && !buffer.released.empty())
		{
			buffer.isPressed = false;
			pop = buffer.released.front();
			total += pop - lastDelta;
			lastDelta = pop;
			buffer.released.pop();
		}
		if (!buffer.isPressed && !buffer.pressed.empty())
		{
			buffer.isPressed = true;
			lastDelta = buffer.pressed.front();
			buffer.pressed.pop();
		}
	}

	if (buffer.isPressed)
		total += delta - lastDelta;

	return total;
}

void Player::buttonPressed(Uint16 button, Uint32 timestamp)
{
	switch (button)
	{
	case InputHandler::UP:
		this->mInputBuffer[0].pressed.push(timestamp);
		break;
	case InputHandler::DOWN:
		this->mInputBuffer[1].pressed.push(timestamp);
		break;
	case InputHandler::LEFT:
		this->mInputBuffer[2].pressed.push(timestamp);
		break;
	case InputHandler::RIGHT:
		this->mInputBuffer[3].pressed.push(timestamp);
		break;
	}
}

void Player::buttonReleased(Uint16 button, Uint32 timestamp)
{
	switch (button)
	{
	case InputHandler::UP:
		this->mInputBuffer[0].released.push(timestamp);
		break;
	case InputHandler::DOWN:
		this->mInputBuffer[1].released.push(timestamp);
		break;
	case InputHandler::LEFT:
		this->mInputBuffer[2].released.push(timestamp);
		break;
	case InputHandler::RIGHT:
		this->mInputBuffer[3].released.push(timestamp);
		break;
	}
}
