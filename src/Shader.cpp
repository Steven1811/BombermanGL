#include "pch.h"
#include "Shader.h"

using namespace Engine;

Shader::Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath)
{
	vPath = vertexShaderPath;
	fPath = fragmentShaderPath;
	compile();
}

//Deletes old Shader, Reloads Shaderfiles, Compiles new Shader
void Shader::compile() {
	//Check if a Shaderprogram is already present
	if (progId != 0) {
		logInfo("Shaderprogram already present. Discarding old Shaderprogram.");
		glDeleteShader(progId);
	}

	//Load File
	// ensure ifstream objects can throw exceptions:
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open files
		vShaderFile.open(vPath);
		logInfo("VertexShader File openend!");
		fShaderFile.open(fPath);
		logInfo("FragmentShader File openend!");
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vCode = vShaderStream.str();
		fCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		logError("Shaderfile not succesfully read!");
	}

	// Convert to traditional C strings
	const GLchar* vShaderCode = vCode.c_str();
	const GLchar* fShaderCode = fCode.c_str();

	// Compile shaders
	GLuint vertex, fragment;
	int success;
	char infoLog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(vertex, 512, NULL, infoLog);
	if (!success)
	{
		logError("%s", infoLog);
	}
	else {
		logInfo("Compilation of VertexShader was successful: %s", infoLog);
	}


	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(fragment, 512, NULL, infoLog);
	if (!success)
	{
		logError("%s", infoLog);
	}
	else {
		logInfo("Compilation of FragmentShader was successful: %s", infoLog);
	}

	// Shader Program
	progId = glCreateProgram();
	glAttachShader(progId, vertex);
	glAttachShader(progId, fragment);
	glLinkProgram(progId);

	// print linking errors if any
	glGetProgramiv(progId, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(progId, 512, NULL, infoLog);
	if (!success)
	{
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

void Shader::setVec3(const std::string &name, glm::vec3* vec3) {
	glUniform3fv(glGetUniformLocation(progId, name.c_str()), 1, glm::value_ptr(*vec3));
}

unsigned int Shader::getProgId() {
	return progId;
}
