#include "GameSystem.h"

#include <iostream>

GameSystem::GameSystem() {
    windowSize.x = 800;
    windowSize.y = 600;
    windowColor.r = 1;
}

GameSystem::~GameSystem() {
    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

void GameSystem::init() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow("Jazz Engine 0.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.x, windowSize.y, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        std::cout << "ERROR: Could not create window\n";
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "ERROR: Could not initialize glad";
    }

    glViewport(0, 0, windowSize.x, windowSize.y);
}

void GameSystem::clearWindow() {
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GameSystem::swapWindow() {
    SDL_GL_SwapWindow(window);
}

void GameSystem::setWindowSize(int width, int height) {
    windowSize.x = width;
    windowSize.y = height;
    if (window != nullptr) {
        SDL_SetWindowSize(window, windowSize.x, windowSize.y);
        glViewport(0, 0, windowSize.x, windowSize.y);
    }
}
