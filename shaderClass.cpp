#include "shaderClass.h"
#include <fstream>
#include <filesystem>

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (!in) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return "";
	}
	std::string contents;
	in.seekg(0, std::ios::end);
	contents.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&contents[0], contents.size());
	in.close();
	return contents;
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	try {
		// Read shader files
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		
		try {
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			
			vShaderFile.close();
			fShaderFile.close();
			
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch(std::ifstream::failure& e) {
			std::string error = "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: ";
			error += std::string(vertexPath) + " or " + std::string(fragmentPath);
			throw std::runtime_error(error);
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		
		// Compile shaders
		GLuint vertex, fragment;
		GLint success;
		char infoLog[512];
		
		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		if (vertex == 0) {
			throw std::runtime_error("Failed to create vertex shader");
		}
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			throw std::runtime_error(std::string("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n") + infoLog);
		}
		
		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		if (fragment == 0) {
			glDeleteShader(vertex);
			throw std::runtime_error("Failed to create fragment shader");
		}
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			glDeleteShader(vertex);
			throw std::runtime_error(std::string("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n") + infoLog);
		}
		
		// Shader Program
		ID = glCreateProgram();
		if (ID == 0) {
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			throw std::runtime_error("Failed to create shader program");
		}
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			throw std::runtime_error(std::string("ERROR::SHADER::PROGRAM::LINKING_FAILED\n") + infoLog);
		}
		
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception& e) {
		ID = 0;
		throw;
	}
}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type) {
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			throw std::runtime_error(std::string("SHADER_COMPILATION_ERROR for: ") + type + "\n" + infoLog);
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			throw std::runtime_error(std::string("SHADER_LINKING_ERROR for: ") + type + "\n" + infoLog);
		}
	}
}



