#include <iostream>
#include "glad/glad.h"
#include <SDL2/SDL.h>

#include "GameSystem/GameSystem.h"
#include "GameSystem/Shader.h"

int main(int argc, char** argv) {
    GameSystem gameSystem;

    //gameSystem.setWindowSize(1280, 720);
    gameSystem.setWindowColor(0.2, 0.2, 0.2, 1.0);
    gameSystem.init();

    Shader shader;
    shader.createShaderProgram("shaders/shader.vert", "shaders/shader.frag");


    //mesh data

    float vertices[] = {
        -0.5f,  0.5f, 0.0f,  // top left
        -0.5f, -0.5f, 0.0f,  // bottom left
        0.5f, -0.5f, 0.0f,  // bottom right
        0.5f,  0.5f, 0.0f,  // top right
    };

    unsigned int indices[] = {
        0, 1, 3,
        3, 1, 2
    };

    unsigned int vboID;
    glGenBuffers(1, &vboID);

    unsigned int eboID;
    glGenBuffers(1, &eboID);

    unsigned int vaoID;
    glGenVertexArrays(1, &vaoID);

    glBindVertexArray(vaoID);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    SDL_Event event;

    bool isRunning = true;
    while (isRunning) {
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_WINDOWEVENT_RESIZED:
                //glViewport(0, 0, 800, 600);
                break;
            }
        }

        gameSystem.clearWindow();

        //glUseProgram(shaderProgram);
        shader.use();

        int uniformLocation = shader.getUniformLocation("time");
        if (uniformLocation != -1) {
            glUniform1f(uniformLocation, SDL_GetTicks());
            std::cout << SDL_GetTicks() << '\n';
        }

        glBindVertexArray(vaoID);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        gameSystem.swapWindow();
    }

    return 0;
}
