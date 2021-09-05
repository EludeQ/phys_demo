cmake_minimum_required(VERSION 3.16)
project(phys_demo)

set(CMAKE_CXX_STANDARD 17)

set(OpenGL_GL_PREFERENCE GLVND)

# Configure raylib
#set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
#add_subdirectory(lib/raylib)
find_package(raylib 3.0 REQUIRED)

add_executable(phys_demo src/main.cpp)

add_subdirectory(src/phys)

target_link_libraries(phys_demo PRIVATE raylib)
# GLM
target_include_directories(phys_demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/glm)