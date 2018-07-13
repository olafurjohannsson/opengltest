//
// Created by olafurj on 11/07/18.
//

#include "window.h"


Window::Window(const char *name, uint32_t screenWidth, uint32_t screenHeight) {
    glfwInit();
    glfwWindowHint( GLFW_SAMPLES, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_TRUE );

    this->window = glfwCreateWindow( screenWidth, screenHeight, name, nullptr, nullptr );
    glfwMakeContextCurrent( this->window );
    glfwSetInputMode( this->window, GLFW_STICKY_KEYS, GL_TRUE );

    /** Initialize GLAD before calling OpenGL functions */
    if ( !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress )) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glfwSetKeyCallback( this->window, [](
            GLFWwindow *window,
            int key,
            int scancode,
            int action,
            int mode) {
        if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
            glfwSetWindowShouldClose( window, GL_TRUE );
        if ( key >= 0 && key < 1024 ) {
            if ( action == GLFW_PRESS ) {
                std::cout << "Key: " << key
                          << "Scancode: " << scancode
                          << "Action: " << action
                          << "Mode: " << mode
                          << "Window: " << window
                          << std::endl;
            } else if ( action == GLFW_RELEASE )
                std::cout << "Key " << key << "released" << std::endl;
        }
    } );

    // OpenGL configuration
    glViewport( 0, 0, screenWidth, screenHeight );
    glfwSetFramebufferSizeCallback( this->window, [](GLFWwindow *window, int width, int height) -> void {
        glViewport( 0, 0, width, height );
    } );

    glEnable( GL_CULL_FACE );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void Window::loop(const Shader &shader,
                  GLuint vertexArrayObjectId,
                  void (*callback)(float)) {
    srand( static_cast<uint32_t >(time( 0 )));
    float r1 = ( static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
    float r2 = ( static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
    float r3 = ( static_cast<float>(rand()) / static_cast<float>(RAND_MAX));

    float deltaTime = 0.0f;
    float lastTime = 0.0f;
    int i = 0;
    shader.use();
    while ( !glfwWindowShouldClose( window )) {
        float currentTime = float( glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        float fps = 1 / deltaTime;
        glfwPollEvents();

        if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS ) {
            glfwSetWindowShouldClose( window, true );
        }

        if (((i++) % 200) == 0) {
            std::cout << "delta: " << deltaTime << std::endl;
            std::cout << "last: " << lastTime << std::endl;
            std::cout << "FPS: " << fps << std::endl;
        }
        callback( fps );


        glClearColor( r1, r2, r3, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );


        glBindVertexArray( vertexArrayObjectId );
        glDrawArrays( GL_TRIANGLES, 0, 3 );


        glfwSwapBuffers( window );

    };
}
