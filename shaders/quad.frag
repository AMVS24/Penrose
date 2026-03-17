#version 430 core
out vec4 FragColor;
in vec2 TexCoords;

uniform float uTime;
uniform vec2 uResolution;
uniform vec3 uCameraPos;

void main() {
    // Map UVs from [0, 1] to [-1, 1] and fix aspect ratio
    vec2 uv = TexCoords * 2.0 - 1.0;
    uv.x *= uResolution.x / uResolution.y;

    // A simple color gradient pulsing with time to prove it works
    vec3 color = vec3(uv.x * 0.5 + 0.5, uv.y * 0.5 + 0.5, abs(sin(uTime)));

    FragColor = vec4(color, 1.0);
}