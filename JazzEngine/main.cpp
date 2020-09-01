#include <iostream>
#include "glad/glad.h"
#include <SDL2/SDL.h>

#include "GameSystem/GameSystem.h"

int main(int argc, char** argv) {
    GameSystem gameSystem;

    //gameSystem.setWindowSize(1280, 720);
    gameSystem.init();



    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success = 0;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR: VERTEX SHADER COMPILATION STAGE FAILED\n";
    }


    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0, 1.0, 0.5, 1.0);\n"
    "}\0";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int f_success = 0;
    char f_infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &f_success);

    if (!f_success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, f_infoLog);
        std::cout << "ERROR: FRAGMENT SHADER COMPILATION STAGE FAILED\n";
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int p_success = 0;
    char p_infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &p_success);

    if (!p_success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, p_infoLog);
        std::cout << "ERROR: SHADER PROGRAM LINK STAGE FAILED\n";
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

        glUseProgram(shaderProgram);
        glBindVertexArray(vaoID);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        gameSystem.swapWindow();
    }

    return 0;
}
