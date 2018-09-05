#ifndef COMPUTE_HPP
#define COMPUTE_HPP

#include <GL\glew.h>
#include <string>
class Compute
{
private:
	GLuint mComputeShader;
	bool CompileShader();
	std::string loadFile(const char *filePath);
public:
	Compute();
	~Compute();

	bool Init();
};

#endif
