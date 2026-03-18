#version 430 core
out vec4 FragColor;
in vec2 TexCoords;

uniform float uTime;
uniform vec2 uResolution;
uniform vec3 uCameraPos;

uniform sampler2D skybox;       // The equirectangular texture sampler
uniform mat4 uInvProjView;      // The inverse View-Projection matrix

const float PI = 3.14159265359;
const float dL = 0.1;

struct ray {
    vec4 x;
    vec4 u;
};

mat4 sph_to_cart_Jacobian(float r, float theta, float phi){ 
    return transpose(mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta),
        0.0, r*cos(theta)*cos(phi), r*cos(theta)*sin(phi), -r*sin(theta),
        0.0, -r*sin(theta)*sin(phi), r*sin(theta)*cos(phi), 0.0
    ));
}
mat4 cart_to_sph_Jacobian(float r, float theta, float phi){
    return inverse(transpose(mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta),
        0.0, r*cos(theta)*cos(phi), r*cos(theta)*sin(phi), -r*sin(theta),
        0.0, -r*sin(theta)*sin(phi), r*sin(theta)*cos(phi), 0.0
    )));
}
ray cart_to_sph(ray R) {
    vec3 p = R.x.yzw;
    float r = length(p);
    float theta = acos(clamp(p.z/(r+1e-8), -1.0, 1.0)); // Avoid division by zero
    float phi = atan(p.y, p.x);
    return ray(vec4(R.x.x,r,theta,phi), cart_to_sph_Jacobian(r, theta, phi) * R.u);
}
ray sph_to_cart(ray R) {
    float r = R.x.y;
    float theta = R.x.z;
    float phi = R.x.w;
    return ray(vec4(R.x.x, r*sin(theta)*cos(phi), r*sin(theta)*sin(phi), r*cos(theta)), sph_to_cart_Jacobian(r, theta, phi) * R.u);
}

vec2 DirectionToUV(vec3 dir) {
    float u = 0.5 + atan(dir.x, dir.z) / (2.0 * PI);
    float v = 0.5 - asin(dir.y) / PI;
    return vec2(u, v);
}

vec3 raymarch(vec3 ro, vec3 rd) {
    ray R = ray(vec4(0.0, ro), vec4(0.0, rd));

    //FIND u.w HERE
    R.u = normalize(R.u);
    float rs = 1; // uniform todo

    ray Rp = cart_to_sph(R);
    //t-0
    //r-1
    //theta-2
    //phi-3
    Rp.u.x = sqrt(
        (
            ((Rp.u.y*Rp.u.y)/(1.0-(rs/Rp.x.y)))
            +(Rp.x.y*Rp.x.y*Rp.u.z*Rp.u.z)
            +(Rp.u.w*Rp.u.w*Rp.x.y*Rp.x.y*sin(Rp.x.z)*sin(Rp.x.z)))
        /(1.0-(rs/Rp.x.y))
        ); //NULL CONSTRAINT

    R = sph_to_cart(Rp);

    //converting cartesian to polar for u and x using jacobian
    

    for(int i = 0; i < 100; i++) {
        if(length(R.x.yzw) < 0.5) { // A simple sphere at (0,0,5) with radius 0.5
            return vec3(1.0, 0.0, 0.0); // Hit the sphere, return red
        }
        // In a real raymarcher, you'd evaluate a distance function here
        R.x.yzw += R.u.yzw * dL; // Step size of 0.1 units
    }
    vec2 skyUV = DirectionToUV(R.u.yzw);
    return texture(skybox, skyUV).rgb; // Return black for now
}

void main() {
    // 1. Generate the initial ray u from this pixel
    // Start with NDC coordinates: x,y in [-1,1]
    vec4 ndcPos = vec4(TexCoords.x * 2.0 - 1.0, TexCoords.y * 2.0 - 1.0, 1.0, 1.0);
    // Un-project from NDC to World Space
    vec4 worldPos = uInvProjView * ndcPos;
    // The ray u is the un-projected u, normalized
    vec3 worldDir = normalize(worldPos.xyz / worldPos.w);

    vec3 finalColor = raymarch(uCameraPos, worldDir);

    // A small animation test to confirm uniforms still work
    finalColor *= abs(sin(uTime * 0.2)) * 0.2 + 0.8;

    FragColor = vec4(finalColor, 1.0);
}