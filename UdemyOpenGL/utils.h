#pragma once
#include <iostream>
#include <format>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>


// OpenGL initialize template
int initWindow(
    int width, int height, const char* title,
    GLFWwindow **pMainWindow, int *pBufferWidth, int *pBufferHeight
);


#define INIT_WINDOW(width, height, title) \
    GLFWwindow* mainWindow; \
    int bufferWidth, bufferHeight; \
    int code = initWindow(width, height, title, &mainWindow, &bufferWidth, &bufferHeight); \
    if (code) \
    { \
        return code; \
    }


/*
    Load shader codes from files.
    Create program; create shaders; compile shaders;
    attach shaders to program; link and validate program.
    Args:
    - filenames of shaders
    Return:
    - program
*/
int CompileShadersProgram(const char* vShader, const char* fShader);


// Load file into a string (for shaders)
std::string LoadFile(const char* filename);