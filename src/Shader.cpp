#include "pch.h"
#include "Shader.h"

using namespace Engine;

Shader::Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open files
		vShaderFile.open(vertexShaderPath);
		fShaderFile.open(fragmentShaderPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		logError("Shaderfile not succesfully read!");
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// 2. compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(vertex, 512, NULL, infoLog);
	if (!success)
	{
		logError("Compilation of VertexShader has failed: %s", infoLog);
	}
	else {
		logInfo("Compilation of VertexShader was successful: %s", infoLog);
	}

	//  fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(fragment, 512, NULL, infoLog);
	if (!success)
	{
		logError("Compilation of FragmentShader has failed: %s", infoLog);
	}
	else {
		logInfo("Compilation of FragmentShader was successful: %s", infoLog);
	}

	// shader Program
	progId = glCreateProgram();
	glAttachShader(progId, vertex);
	glAttachShader(progId, fragment);
	glLinkProgram(progId);

	// print linking errors if any
	glGetProgramiv(progId, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(progId, 512, NULL, infoLog);
	if (!success)
	{
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		logError("Linking Fragment- and VertexShaders together has failed: %s", infoLog);
	}
	else {
		logInfo("Linking Fragment- and VertexShaders together was successful: %s", infoLog);
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(progId);
}

void Shader::setBool(const std::string &name, bool value)
{
	glUniform1i(glGetUniformLocation(progId, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value)
{
	glUniform1i(glGetUniformLocation(progId, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value)
{
	glUniform1f(glGetUniformLocation(progId, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4* mat4) {
	glUniformMatrix4fv(glGetUniformLocation(progId, name.c_str()), 1, GL_FALSE, glm::value_ptr(*mat4));
}

unsigned int Shader::getProgId() {
	return progId;
}
