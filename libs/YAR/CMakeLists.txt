cmake_minimum_required(VERSION 3.10)

project(yar)

add_library(${PROJECT_NAME} src/Renderer.cpp src/Picture.cpp src/Screen.cpp src/World.cpp src/Entity.cpp src/Triangle.cpp src/Object.cpp src/Camera.cpp src/Color.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include ../glm/glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)
