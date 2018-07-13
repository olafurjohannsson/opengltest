//
// Created by olafurj on 10/07/18.
//

#ifndef NAME_SHADER_H
#define NAME_SHADER_H

#include <cstring>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "util.h"

namespace {
    bool stringEqual(const char *str1, const char *str2) {
        return strcmp( str1, str2 ) == 0;
    }
}

/**
 * Loads and compiles shaders
 */
class Shader {
public:

    Shader() {
        this->fragmentShaderId = this->compile( GL_FRAGMENT_SHADER, "/home/olafurj/dev/opengltest/fragment.shader" );
        this->vertexShaderId = this->compile( GL_VERTEX_SHADER, "/home/olafurj/dev/opengltest/vertex.shader" );
        this->shaderProgramId = this->link();
    }

    void use() const {
        glUseProgram( this->shaderProgramId );
    }

private:
    uint32_t fragmentShaderId;
    uint32_t vertexShaderId;
    uint32_t shaderProgramId;

    /**
     * Create and link program
     * @return 
     */
    uint32_t link() {
        /** Create program and attach to shaders **/
        uint32_t pid = glCreateProgram();
        glAttachShader( pid, this->vertexShaderId );
        glAttachShader( pid, this->fragmentShaderId );
        glLinkProgram( pid );

        this->checkCompilerErrors( pid, "PROGRAM" );

        /** Use program and clean resources **/
        glUseProgram( pid );
        glDeleteShader( this->vertexShaderId );
        glDeleteShader( this->fragmentShaderId );

        return pid;
    }


    uint32_t compile(uint32_t shaderType, const std::string &path) {
        /** Create shader **/
        uint32_t shader = glCreateShader( shaderType );

        /** Read shader code **/
        std::string src = Util::readFile( path );
        if ( !src.empty()) {
            const char *vertexShaderSource = src.c_str();
            /** Read shader code and compile **/
            glShaderSource( shader, 1, &vertexShaderSource, NULL );
            glCompileShader( shader );

            this->checkCompilerErrors( shader, "LINK" );
        }

        return shader;
    }

    void checkCompilerErrors(uint32_t object, const char *type) {
        int32_t success;
        char infoLog[1024];

        if ( ::stringEqual(type, "PROGRAM") ) {
            glGetProgramiv( object, GL_LINK_STATUS, &success );
            if ( !success ) {
                glGetProgramInfoLog( object, 1024, NULL, infoLog );
            }
        } else {
            glGetShaderiv( object, GL_COMPILE_STATUS, &success );
            if ( !success ) {
                glGetShaderInfoLog( object, 1024, NULL, infoLog );
            }
        }


        if ( !success ) {
            std::cout << "ERROR::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

};

#endif //NAME_SHADER_H
