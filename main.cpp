#include <iostream>
#include <thread>
#include <functional>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

#define _GLAD 1


#ifdef _GLAD

#include <glad/glad.h>

#else
/**
 * OpenGL Extension Wrangler (Same as GLAD)
 */
#include <GL/glew.h>
#endif


/**
 * OpenGL Utility Toolkit
 */
//#include <GL/glut.h>

/**
 * Graphics Library Framework (GLFW)
 * Handles creating windows and OpenGL contexts, and joystick/keyboard/mouse
 */
#include <GLFW/glfw3.h>

/**
 * OpenGL Mathematics (GLM)
 * Mathematics library for graphics software
 */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include "window.h"
#include "shader.h"
const uint32_t CNT = 9;
float verticestest[] {
        -0.7f, -0.5f, 0.0f,
        0.7f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
};

void generate_vertices(float vertices[]) {
    float vert[CNT];
    for ( int i = 0; i < CNT; ++i ) { vert[ i ] = ( static_cast<float>(rand()) / static_cast<float>(RAND_MAX)); }
    memcpy((void *) vertices, vert, CNT );
}

void f() {

}

int main() {
    srand( static_cast<uint32_t >(time( 0 )));

    Window wnd( "test", 800, 600 );

    /**
     * Create shader manipulator
     */
    Shader shader;

    /**
     * Bind to Array buffer, all calls to GL_ARRAY_BUFFER after this call
     * will be on that singleton
     * Copy user-defined vertices into vertex buffer object
     * currently bound to the GL_ARRAY_BUFFER target.
     */
    GLuint vertexBufferObjectId;
    glGenBuffers( 1, &vertexBufferObjectId );
    glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObjectId );
//    float vertices[9];
//    generate_vertices( vertices );
    float vertices[CNT];
    memcpy(vertices, verticestest, CNT);
    //generate_vertices(vertices);
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    GLuint vertexArrayObjectId;
    glGenVertexArrays( 1, &vertexArrayObjectId );
    glBindVertexArray( vertexArrayObjectId );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( GL_FLOAT ), (void *) 0 );
    glEnableVertexAttribArray( 0 );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );


    wnd.loop( shader, vertexArrayObjectId, [](float fps) {


    } );


    glDeleteVertexArrays( 1, &vertexArrayObjectId );
    glDeleteBuffers( 1, &vertexBufferObjectId );


    return EXIT_SUCCESS;
}


/**

 A fragment in OpenGL is all the data required for OpenGL to render a single pixel.

GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
GL_DYNAMIC_DRAW: the data is likely to change a lot.
GL_STREAM_DRAW: the data will change every time it is drawn.

 */