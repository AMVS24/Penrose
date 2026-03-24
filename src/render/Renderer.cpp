#include "Renderer.h"

Renderer::Renderer() {
    // 5. Setup the Full-Screen Quad Geometry
    float quadVertices[] = {
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    
    // Position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    // Texture coordinate attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

Renderer::~Renderer() {
    // 7. Cleanup
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
}

void Renderer::draw(Shader& shader, GLFWwindow* window, Camera& camera, unsigned int skyboxTexture, float currentFrame) {
    // Activate shader and pass uniforms to GPU
    shader.use();
    shader.setFloat("uTime", currentFrame);
    
    // Pass the actual window size (important for resizing)
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    shader.setVec2("uResolution", glm::vec2((float)width, (float)height));
    
    // Setup initial camera position
    shader.setVec3("uCameraPos", camera.Position);

    // Create standard view and projection matrices
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    
    // Pass them to the shader
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "uViewMatrix"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "uProjectionMatrix"), 1, GL_FALSE, &projection[0][0]);
    // Also pass the inverse for easy ray generation
    glm::mat4 invProjView = glm::inverse(projection * view);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "uInvProjView"), 1, GL_FALSE, &invProjView[0][0]);

    particleBuffer.bind(0);
    // Pass particle count to shader
    shader.setInt("uParticleCount", (int)particleBuffer.getParticleCount());

    // Bind the skybox texture to unit 0 before drawing
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, skyboxTexture);

    // Draw the quad
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::updateParticles(const std::vector<Particle>& particles) {
    particleBuffer.uploadParticles(particles);
}