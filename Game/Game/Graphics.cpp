#include "Graphics.hpp"

#include <fstream>
#include <sstream>

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

void Graphics::init()
{
	this->mPrograms.push_back(this->compileProgram("pass.vert", "pass.frag"));
	//? Where should I do this?
	//x glEnableVertexAttribArray(0);
}

void Graphics::useProgram(GLuint i)
{
	//Todo Error handling here
	glUseProgram(this->mPrograms[i]);
	this->currentProgram = this->mPrograms[i];
}

GLuint Graphics::getCurrentProgram() const
{
	return this->currentProgram;
}

GLint Graphics::getWorldLocation() const
{
	return glGetUniformLocation(this->currentProgram, "world");
}

GLuint Graphics::compileProgram(const char *pVertexPath, const char *pFragmentPath, const char *pGeometryPath)
{
	std::string vertex, fragment, geometry;

	vertex = this->loadFile(pVertexPath);
	fragment = this->loadFile(pFragmentPath);
	if (pGeometryPath != nullptr)
		geometry = this->loadFile(pGeometryPath);

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	this->compileShader(vertexShaderID, vertex.c_str());

	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	this->compileShader(fragmentShaderID, fragment.c_str());

	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	if (pGeometryPath != nullptr)
	{
		GLuint geometryShaderID;
		geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
		this->compileShader(geometryShaderID, geometry.c_str());

		glAttachShader(programID, geometryShaderID);
	}

	glLinkProgram(programID);

	GLint result;

	glGetShaderiv(programID, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		//x GLint logLenght = 0;
		GLchar logString[1024];
		//x glGetShaderiv(programID, GL_INFO_LOG_LENGTH, &logLenght);
		std::stringstream ss;
		glGetShaderInfoLog(programID, 1024, NULL, logString);
		ss << logString;
		throw ss.str();
	}

	return programID;
}

std::string Graphics::loadFile(const char *pFilePath)
{
	std::string returnCode;
	std::ifstream streamCode(pFilePath);
	if (streamCode.is_open())
	{
		std::stringstream ss;
		ss << streamCode.rdbuf();
		returnCode = ss.str();
		streamCode.close();
	}
	else
	{
		std::stringstream ss;
		ss << "Shader missing at " << pFilePath;
		throw ss.str();
	}
	return returnCode;
}

void Graphics::compileShader(GLuint ID, const char *pTextPointer)
{
	GLint result;
	glShaderSource(ID, 1, &pTextPointer, NULL);
	glCompileShader(ID);

	glGetShaderiv(ID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		//x GLint logLenght = 0;
		GLchar logString[1024];
		//x glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logLenght);
		std::stringstream ss;
		glGetShaderInfoLog(ID, 1024, NULL, logString);
		ss << logString;
		throw ss.str();
	}
}
