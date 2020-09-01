#include "Shader.h"

#include <fstream>

Shader::Shader() {
    //
}

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {
    createShaderProgram(vertexShaderPath, fragmentShaderPath);
}

Shader::~Shader() {
    if (shaderProgram != -1) {
        glDeleteProgram(shaderProgram);
        shaderProgram = -1;
    }
}

void Shader::createShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath) {
    std::string vertexShaderSource = getFileContents(vertexShaderPath);
    std::string fragmentShaderSource = getFileContents(fragmentShaderPath);

    unsigned int vertexShader;
    compileShader(GL_VERTEX_SHADER, &vertexShader, vertexShaderSource.c_str());

    unsigned int fragmentShader;
    compileShader(GL_FRAGMENT_SHADER, &fragmentShader, fragmentShaderSource.c_str());

    shaderProgram = glCreateProgram();
    linkProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

bool Shader::compileShader(GLenum SHADER_TYPE, unsigned int *shader, const char* src) {
    *shader = glCreateShader(SHADER_TYPE);
    glShaderSource(*shader, 1, &src, NULL);
    glCompileShader(*shader);

    int success = 0;
    char infoLog[512];
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(*shader, 512, NULL, infoLog);
        std::cout << "ERROR: SHADER COMPILATION STAGE FAILED " << infoLog << '\n';
        std::cout << glGetError() << '\n';
    }

    return success;
}

void Shader::use() {
    glUseProgram(shaderProgram);
}

int Shader::getUniformLocation(const char* name) {
    return glGetUniformLocation(shaderProgram, name);
}

std::string Shader::getFileContents(std::string path) {
    std::ifstream file;
    file.open(path);

    std::string line = "";
    std::string fileContents = "";
    if (file.good()) {
        while (std::getline(file, line)) {
            fileContents += line + '\n';
            //std::cout << "CONTENTS: " << fileContents << '\n';
        }
    }
    else {
        std::cout << "Cant open file: " << path << '\n';
    }
    std::cout << fileContents << '\n';
    file.close();

    return fileContents;
}

bool Shader::linkProgram(unsigned int& vertexShader, unsigned int& fragmentShader) {
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success = 0;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR: SHADER PROGRAM LINK STAGE FAILED " << infoLog << '\n';
    }

    return success;
}
