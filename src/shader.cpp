#include <shader.h>
#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>


Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) {
	load(vertexSource, fragmentSource);
}

Shader::Shader(const Path& vertexPath, const Path& fragmentPath) {

	
	//load sources from files
	try {
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		load(vShaderStream.str(), fShaderStream.str());

	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCESSFULLY_READ" << std::endl;
	}

}




void Shader::load(const std::string& vertexSource, const std::string& fragmentSource) {

	const char* vShaderCode = vertexSource.c_str();
	const char* fShaderCode = fragmentSource.c_str();

	auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
	glCompileShader(fragmentShader);

	success;
	infoLog;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	//Link them together (what was compiled)
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, vertexShader);
	glAttachShader(_shaderProgram, fragmentShader);
	glLinkProgram(_shaderProgram);

	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::LINK_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Bind() {

	//Use our triangle shader
	glUseProgram(_shaderProgram);
}

GLuint Shader::getUniformLocation(const std::string& uniformName){
	
	return glGetUniformLocation(_shaderProgram, uniformName.c_str());
}

void Shader::SetMat4(const std::string& uniformName, const glm::mat4& mat4) {
	auto uniformLoc = getUniformLocation(uniformName);

	if (uniformLoc != -1) {
		
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(mat4));
	}
}

void Shader::SetInt(const std::string& uniformName, int value){
	auto uniformLoc = getUniformLocation(uniformName);

	if (uniformLoc != -1) {
		
		glUniform1i(uniformLoc,value);
	}
}

void Shader::SetVec3(const std::string& uniformName, const glm::vec3& value){
	auto uniformLoc = getUniformLocation(uniformName);

	if (uniformLoc != -1) {

		glUniform3fv(uniformLoc, 1, &value[0]);
	}
}

void Shader::SetVec3(const std::string& uniformName, float x, float y, float z) {
	auto uniformLoc = getUniformLocation(uniformName);

	if (uniformLoc != -1) {

		glUniform3f(uniformLoc, x, y, z);
	}
}

void Shader::SetFloat(const std::string& uniformName, float value){
	auto uniformLoc = getUniformLocation(uniformName);

	if (uniformLoc != -1) {

		glUniform1f(uniformLoc, value);
	}
}

