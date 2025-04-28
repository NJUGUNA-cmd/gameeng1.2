#version 330 core

// Input vertex attribute from the VAO (usually a rectangle covering the screen)
layout(location = 0) in vec3 aPos; 

// Output to the fragment shader
out vec2 fragCoord;

// Uniforms for transforming coordinates
uniform vec2 uResolution;

void main() {
    // Pass the position in clip space (-1.0 to 1.0) as texture coordinates to the fragment shader
    fragCoord = (aPos.xy * 0.5 + 0.5) * uResolution;

    // Set the position of the vertex in screen space
    gl_Position = vec4(aPos, 1.0);
}
