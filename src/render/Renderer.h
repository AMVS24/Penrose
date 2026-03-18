#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

class Renderer {
private:
    unsigned int quadVAO, quadVBO;

public:
    Renderer();
    ~Renderer();

    // draw function called by main
    void draw(Shader& shader, GLFWwindow* window, Camera& camera, unsigned int skyboxTexture, float currentFrame);
};