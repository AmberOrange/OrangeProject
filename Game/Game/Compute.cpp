#include "Compute.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

bool Compute::CompileShader()
{
	GLint result;
	std::string vertex = this->loadFile("pass.comp");
	if (vertex == "")
		return false;
	const char* vertexPtr = vertex.c_str();

	GLuint compute = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(compute, 1, &vertexPtr, NULL);
	glCompileShader(compute);

	glGetShaderiv(compute, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		//x GLint logLenght = 0;
		GLchar logString[1024];
		//x glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logLenght);
		std::stringstream ss;
		glGetShaderInfoLog(compute, 1024, NULL, logString);
		ss << logString;
		std::cout << ss.str();
		return false;
	}

	this->mComputeShader = glCreateProgram();
	glAttachShader(this->mComputeShader, compute);
	glLinkProgram(this->mComputeShader);



	glGetShaderiv(this->mComputeShader, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		//x GLint logLenght = 0;
		GLchar logString[1024];
		//x glGetShaderiv(programID, GL_INFO_LOG_LENGTH, &logLenght);
		std::stringstream ss;
		glGetShaderInfoLog(this->mComputeShader, 1024, NULL, logString);
		ss << logString;
		std::cout << ss.str();
		return false;
	}
	return true;
}

std::string Compute::loadFile(const char *filePath)
{
	std::string returnCode;
	std::ifstream streamCode(filePath);
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
		std::cout << "Shader missing at " << filePath;
		return "";
	}
	return returnCode;
}

Compute::Compute()
{
}

Compute::~Compute()
{
}

bool Compute::Init()
{
	if (!this->CompileShader())
		return false;
	return true;
}
