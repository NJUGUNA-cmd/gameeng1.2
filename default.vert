#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;

// Colors
layout (location = 1) in vec3 aColor;

// Texture Coordinates
layout (location = 2) in vec2 aTex;

//normals
layout(location=3)in vec3 aNormal;


// Outputs the color for the Fragment Shader
out vec3 color;

// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

//output the normal for the frag shader
out vec3 Normal;

//outputs the current position for the fragment shader;
out vec3  crntPos;


//imports the camera matrix from the main function
uniform mat4 camMatrix;

//import the model matrix from the main function
uniform mat4 model;


void main()
{
	//calculate the current position
	crntPos= vec3(model*vec4(aPos, 1.0f));


	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix*vec4(aPos,1.0);

	// Assigns the colors from the Vertex Data to "color"
	color = aColor;

	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;

	//assigning the normal from the vertex Data to normal
	Normal=aNormal;
}