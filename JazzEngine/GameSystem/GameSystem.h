#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "glad/glad.h"
#include <SDL2/SDL.h>

class GameSystem {
public:
    GameSystem();
    ~GameSystem();

    void init();
    void clearWindow();
    void swapWindow();
    void setWindowSize(int width, int height);
private:
    SDL_Window* window = nullptr;

    SDL_Point windowSize;
    SDL_Color windowColor;
};

#endif // GAMESYSTEM_H
