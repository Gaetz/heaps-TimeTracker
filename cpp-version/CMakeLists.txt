cmake_minimum_required(VERSION 3.15)
project(TimeTracker VERSION 0.1.0)

set(OpenGL_GL_PREFERENCE "GLVND")
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

# Includes and libraries
if (WIN32)
    set(SDL2_DIR ${CMAKE_SOURCE_DIR}/external/SDL2-2.0.12)
    set(SDL2_image_DIR ${CMAKE_SOURCE_DIR}/external/SDL2_image-2.0.5)
    set(GLEW_DIR ${CMAKE_SOURCE_DIR}/external/glew-2.1.0)
endif (WIN32)


find_package(OpenGL REQUIRED COMPONENTS OpenGL)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_image_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(OpenGL)

# subdirectories
add_subdirectory( src/engine )
add_subdirectory( src/game )

# Executable and link
if (NOT WIN32)
    string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
endif (NOT WIN32)
add_executable(TimeTracker src/main.cpp)
target_link_libraries(TimeTracker game engine maths ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_image_LIBRARIES} OpenGL::GL OpenGL::GLU)


if (WIN32)
    file(COPY external/SDL2-2.0.12/lib/x64/SDL2.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
    file(COPY external/SDL2_mixer-2.0.4/lib/x64/SDL2_mixer.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
    file(COPY external/SDL2_image-2.0.5/lib/x64/SDL2_image.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
    file(COPY external/SDL2_image-2.0.5/lib/x64/libpng16-16.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
    file(COPY external/SDL2_image-2.0.5/lib/x64/libjpeg-9.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
    file(COPY external/SDL2_image-2.0.5/lib/x64/zlib1.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
    file(COPY external/SDL2_ttf-2.0.15/lib/x64/SDL2_ttf.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
    file(COPY external/SDL2_ttf-2.0.15/lib/x64/zlib1.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
    file(COPY external/glew-2.1.0/bin/Release/x64/glew32.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
endif (WIN32)

if (WIN32)
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/Debug)
else (WIN32)
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
endif (WIN32)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
