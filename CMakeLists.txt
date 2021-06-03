cmake_minimum_required(VERSION 3.10)

project(MyCourseProject VERSION 0.0.1
                        DESCRIPTION  "HSE AMI 2 Year Course Project"
                        LANGUAGES CXX)
add_subdirectory(libs/glm)
add_subdirectory(libs/SFML)
add_subdirectory(libs/YAR)

add_executable(app src/main.cpp src/Application.cpp)
target_include_directories(app PUBLIC src libs/YAR/include libs/SFML/include)
target_compile_features(app PUBLIC cxx_std_17)
target_link_libraries(app PUBLIC yar sfml-graphics sfml-window sfml-system)
