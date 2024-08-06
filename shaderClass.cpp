#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);

}
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//Create Vertex Shader object and get its reference
	GLuint vertexShader = glCreateShader(GL_FRAGMENT_SHADER);
	//ATTACH Vertex shader source to the vertex  shader object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	//create Fragment Shader object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//ATTACH fragment shader source to the fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//compile the fragment Shader into machene code
	glCompileShader(fragmentShader);


	//Create Shad program object and  its reference
	ID= glCreateProgram();
	//ATTATCH THE VERTEX AND FRAGMENT SHADERS TO THE SHADER PROGRAM
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//Wrap-up/Link all the shaders together into the shader Program
	glLinkProgram(ID);

	//Delete the now useless vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
void Shader::Activate()
{
	glUseProgram(ID);
}
void Shader::Delete()
{
	glDeleteProgram(ID);
}