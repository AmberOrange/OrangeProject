#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include <GL\glew.h>
#include <string>
#include <vector>

class Graphics
{
public:
	Graphics();
	~Graphics();

	void init();
	void useProgram(GLuint i);
	GLuint getCurrentProgram() const;
	GLint getWorldLocation() const;
private:
	std::vector<GLuint> mPrograms;
	GLuint currentProgram;

	GLuint compileProgram(
		const char *pVertexPath,
		const char *pFragmentPath,
		const char *pGeometryPath = nullptr);
	std::string loadFile(const char *pFilePath);
	void compileShader(GLuint ID, const char *pTextPointer);
};

#endif