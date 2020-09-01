#ifndef SHADER_H
#define SHADER_H

#include <iostream>

#include "glad/glad.h"
#include <SDL2/SDL.h>

class Shader {
public:
    Shader();
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
    ~Shader();

    void createShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);

    void use();
    int getUniformLocation(const char* name);
private:
    bool compileShader(GLenum SHADER_TYPE, unsigned int *shader, const char* src);
    std::string getFileContents(std::string path);
    bool linkProgram(unsigned int& vertexShader, unsigned int& fragmentShader);

    unsigned int shaderProgram = -1;
};

#endif // SHADER_H
