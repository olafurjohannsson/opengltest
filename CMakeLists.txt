cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(NAME opengltest)
project({NAME})

# Set preprocessor defines
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOMINMAX -D_USE_MATH_DEFINES")

# Clang specific stuff
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-switch-enum")
endif()

# Debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wextra -Wundef")
endif(CMAKE_COMPILER_IS_GNUCXX)


#find_path(GLEW_INCLUDE_DIR GL/glew.h)
#find_package(ASSIMP REQUIRED)

find_package(Threads REQUIRED)
find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
#find_package(GLUT REQUIRED)
find_package(glm REQUIRED)


add_executable(opengltest main.cpp includes/glad/include/glad/glad.c shader.h util.h game.h window.cpp window.h)

target_include_directories(opengltest PUBLIC
        ${OPENGL_INCLUDE_DIR}
        includes/glad/include
        )
# -l command
target_link_libraries(opengltest
        glfw
        dl
        ${OPENGL_gl_LIBRARY}
        )

MESSAGE("ASDF ${OPENGL_gl_LIBRARY} ${OPENGL_INCLUDE_DIR}")
MESSAGE("Dds")

MESSAGE("DONE")
