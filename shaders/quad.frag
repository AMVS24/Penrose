#version 430 core
out vec4 FragColor;
in vec2 TexCoords;

uniform float uTime;
uniform vec2 uResolution;
uniform vec3 uCameraPos;

uniform sampler2D skybox;       // The equirectangular texture sampler
uniform mat4 uInvProjView;      // The inverse View-Projection matrix

const float PI = 3.14159265359;
const float dT = 0.1;

vec2 DirectionToUV(vec3 dir) {
    float u = 0.5 + atan(dir.x, dir.z) / (2.0 * PI);
    float v = 0.5 - asin(dir.y) / PI;
    return vec2(u, v);
}

vec3 raymarch(vec3 ro, vec3 rd) {
    vec4 u = vec4(rd,0.0);
    vec4 x = vec4(ro,0.0);

    //FIND u.w HERE

    for(int i = 0; i < 100; i++) {
        if(length(ro.xyz-vec3(0.0, 0.0, 0.0)) < 0.5) { // A simple sphere at (0,0,5) with radius 0.5
            return vec3(1.0, 0.0, 0.0); // Hit the sphere, return red
        }
        // In a real raymarcher, you'd evaluate a distance function here
        ro += rd * dT; // Step size of 0.1 units
    }
    vec2 skyUV = DirectionToUV(rd);
    return texture(skybox, skyUV).rgb; // Return black for now
}

void main() {
    // 1. Generate the initial ray direction from this pixel
    // Start with NDC coordinates: x,y in [-1,1]
    vec4 ndcPos = vec4(TexCoords.x * 2.0 - 1.0, TexCoords.y * 2.0 - 1.0, 1.0, 1.0);
    // Un-project from NDC to World Space
    vec4 worldPos = uInvProjView * ndcPos;
    // The ray direction is the un-projected direction, normalized
    vec3 worldDir = normalize(worldPos.xyz / worldPos.w);

    vec3 finalColor = raymarch(uCameraPos, worldDir);

    // A small animation test to confirm uniforms still work
    finalColor *= abs(sin(uTime * 0.2)) * 0.2 + 0.8;

    FragColor = vec4(finalColor, 1.0);
}