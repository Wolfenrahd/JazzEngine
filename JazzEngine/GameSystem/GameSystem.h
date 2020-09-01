#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "glad/glad.h"
#include <SDL2/SDL.h>

struct ColorF {
    float r = 1.0;
    float g = 1.0;
    float b = 1.0;
    float a = 1.0;
};

class GameSystem {
public:
    GameSystem();
    ~GameSystem();

    void init();
    void clearWindow();
    void swapWindow();
    void setWindowSize(int width, int height);
    void setWindowColor(float r, float g, float b, float a);
private:
    SDL_Window* window = nullptr;

    SDL_Point windowSize;
    ColorF windowColor;
};

#endif // GAMESYSTEM_H
