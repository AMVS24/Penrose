#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

// Physics headers
#include "Constants.h"

// Rendering headers
#include "render/Shader.h"
#include "render/Window.h"
#include "render/Camera.h"
#include "render/Texture.h"
#include "render/Renderer.h"
#include "render/Particle.h"
#include "render/FrameCapture.h"

#ifdef _WIN32
extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.5f, 0.0f, 2.0f));

float deltaTime = 0.0f; 
float lastFrame = 0.0f; 

int main() {
    // 0. Register GLFW Error Callback
    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
    });

    // 1. Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. Create the Window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Penrose: RK4 Black Hole", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 3. Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Print runtime OpenGL information
    std::cout << "========================================" << std::endl;
    std::cout << "OpenGL Version:  " << glGetString(GL_VERSION) << std::endl;
    std::cout << "OpenGL Vendor:   " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GLSL Version:    " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "========================================" << std::endl;

    // 4. Load the Shader Program & Textures
    Shader shader("../../shaders/quad.vert", "../../shaders/quad.frag");

    unsigned int skyboxTexture = loadTexture("../../shaders/starfield_original.jpg");
    if (skyboxTexture == 0) return -1; // Fail if image didn't load

    // 5. Setup the Full-Screen Quad Geometry
    Renderer renderer; // The constructor silently builds the VAO/VBO here!

    // Create some test particles
    std::vector<Particle> particles; // Kept empty to remove the red and green test particles

    // Upload to renderer
    renderer.updateParticles(particles);
    
    shader.use();
    shader.setInt("skybox", 0);

    // Initialize frame capture
    FrameCapture frameCapture;

    // 6. Main Render Loop
    while (!glfwWindowShouldClose(window)) {
        // --- TIMING MATH ---
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // --- PROCESS KEYBOARD INPUT ---
        // uses the global camera and deltaTime(=dt by default)
        processInput(window, camera, frameCapture);

        // --- CLEAR SCREEN ---
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // --- UPDATE ---
        // Update particle data if needed
        //test update
        for (Particle& p : particles) {
            p.stateX.z += deltaTime *0.01; // Increment time
        }
        renderer.updateParticles(particles);

        // --- DRAW Fn ---
        renderer.draw(shader, window, camera, skyboxTexture, currentFrame);

        // --- CAPTURE FRAME IF ENABLED ---
        if (frameCapture.getIsCapturing()) {
            std::string filePath = frameCapture.getNextFilePath();
            renderer.captureFrame(filePath, window);
        }

        // --- SWAP BUFFERS ---
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 7. Cleanup
    glfwTerminate();
    return 0;
}