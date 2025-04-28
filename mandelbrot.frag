#version 330 core
out vec4 FragColor;

uniform vec2 uResolution;  // window resolution
uniform float uZoom;       // zoom level
uniform vec2 uOffset;      // pan offset

void main() {
    vec2 c = (gl_FragCoord.xy - uResolution * 0.5) / uZoom + uOffset;
    vec2 z = vec2(0.0);
    int iterations = 0;
    const int maxIterations = 1000;
    
    for (int i = 0; i < maxIterations; ++i) {
        if (dot(z, z) > 4.0) break;
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
        iterations++;
    }

    float t = float(iterations) / float(maxIterations);
    vec3 color = vec3(t, t * 0.5, t * 0.3);
    FragColor = vec4(color, 1.0);
}
