cmake_minimum_required (VERSION 2.8)

project (OpenGLProject)

option(USE_CLANG "build application with clang" OFF) # OFF is the default
if(USE_CLANG)
    SET(CMAKE_CXX_COMPILER  "/usr/bin/clang++")
endif(USE_CLANG)

add_definitions(-std=c++11 -O2 -Wall -Wextra -pedantic)

# OpenGL
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL not found!")
endif(NOT OPENGL_FOUND)
include_directories(${OPENGL_INCLUDE_DIR})
#target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

# GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
if(NOT GLFW_FOUND)
    message(FATAL_ERROR "GLFW not found")
endif(NOT GLFW_FOUND)
include_directories(${GLFW_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})

# GLEW
find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
    message(FATAL_ERROR "GLEW not found!")
endif(NOT GLEW_FOUND)
include_directories(${GLEW_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})

# SOIL
include(FindSOIL.cmake)
if(NOT SOIL_FOUND)
    message(FATAL_ERROR "SOIL not found!")
endif(NOT SOIL_FOUND)
include_directories(${SOIL_INCLUDE_DIR})
#target_link_libraries(${PROJECT_NAME} ${SOIL_LIBRARY})

# Set Libraries
set(LIBRARIES ${GLEW_LIBRARIES} ${SOIL_LIBRARY} ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})

include_directories(
    ${CMAKE_SOURCE_DIR}/Models
    ${CMAKE_SOURCE_DIR}/Shader
    ${CMAKE_SOURCE_DIR}/Source
)

#file(GLOB Game_HEAD
#    Source/"*.cpp"
#)

#file(GLOB Game_SRC
#    Source/"*.cpp"
#)

set(Game_HEAD   Source/main.h
                Source/Camera.h
                Source/Game.h
                Source/GameObject.h
                Source/GLerror.h
                Source/keyCallback.h
                Source/loadShader.h
                Source/ModelLoader.h
                Source/Texture.h)

set(Game_SRC    Source/main.cpp
                Source/Camera.cpp
                Source/Game.cpp
                Source/GameObject.cpp
                Source/GLerror.cpp
                Source/keyCallback.cpp
                Source/loadShader.cpp
                Source/ModelLoader.cpp
                Source/Texture.cpp)

#message(${Game_SRC})
#message(${Game_HEAD})
add_executable(game ${Game_SRC} ${Game_H})
target_link_libraries(game ${LIBRARIES} )
