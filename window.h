//
// Created by olafurj on 11/07/18.
//

#ifndef NAME_WINDOW_H
#define NAME_WINDOW_H

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include "shader.h"


/**
 * Window
 */
class Window {
public:

    Window(const char *name, uint32_t screenWidth, uint32_t screenHeight);

    ~Window() {
        glfwTerminate();
    }

    void loop(const Shader &shader,
              GLuint vertexArrayObjectId,
              void (*pFunction)(float));

private:
    GLFWwindow *window;


};


#endif //NAME_WINDOW_H
