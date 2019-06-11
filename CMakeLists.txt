cmake_minimum_required(VERSION 3.0.2)

project(queengine LANGUAGES CXX)
set(ENGINE_NAME queengine)

option(RELEASE_BUILD "Release build" OFF)

if (RELEASE_BUILD)
    message("== Release BUILD ==")
    set(ENGINE_RESOURCES_FOLDER "/usr/engine/${ENGINE_NAME}-resources")
else()
    message("== Debug BUILD ==")
    set(ENGINE_RESOURCES_FOLDER "engine")
endif()

set(ENGINE_ASSETS_FOLDER "${ENGINE_RESOURCES_FOLDER}/assets")

set (PROJECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/engine/include")
set (PROJECT_SRC_DIR     "${PROJECT_SOURCE_DIR}/engine/src")
set (PROJECT_ASSETS_DIR  "${PROJECT_SOURCE_DIR}/engine/assets")
set (PROJECT_LIBS_DIR    "${PROJECT_SOURCE_DIR}/libs")


# Gets the list of files inside the src directory
file(GLOB_RECURSE SOURCES "${PROJECT_SRC_DIR}/*.cpp"
                          "${PROJECT_SRC_DIR}/*.c")
# Include Headers
include_directories(${PROJECT_INCLUDE_DIR})

#### Compilation ####
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compilation Flags
set(COMPILE_FLAGS "")

if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    set(COMPILE_FLAGS "${COMPILE_FLAGS} -std=c++11 -W -Wall -pedantic -Wshadow -ldl -lrt -lnsl -ld -lGL -lGLU -lm -lX11 -lXxf86vm -lpthread -lXrandr -pthread -lXi -g")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    set(COMPILE_FLAGS "${COMPILE_FLAGS} -std=c++11 -W -Wall -pedantic -Wshadow -ldl -lrt -lnsl -ld -lGL -lGLU -lm -lX11 -lXxf86vm -lpthread -lXrandr -pthread -lXi -g")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(COMPILE_FLAGS "${COMPILE_FLAGS} /Wall")
endif()

# GLAD
add_subdirectory("${PROJECT_LIBS_DIR}/glad")
include_directories("${PROJECT_LIBS_DIR}/glad/include")

# GLM
add_subdirectory("${PROJECT_LIBS_DIR}/glm")
include_directories("${PROJECT_LIBS_DIR}/glm")

# STB
include_directories("${PROJECT_LIBS_DIR}/stb")


## Executable

add_executable(${ENGINE_NAME} ${SOURCES})
target_link_libraries(${ENGINE_NAME} glad dl SDL2 SDL2_image SDL2_ttf SDL2_mixer)


#### Custom Commands ####

# Copy assets folder to build
add_custom_command(TARGET ${ENGINE_NAME} PRE_BUILD
   COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/engine"
   COMMENT "mkdir ${CMAKE_BINARY_DIR}/engine")
add_custom_command(TARGET ${ENGINE_NAME} PRE_BUILD
   COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_ASSETS_DIR} "${CMAKE_BINARY_DIR}/${ENGINE_ASSETS_FOLDER}"
   COMMENT "symlink ${PROJECT_ASSETS_DIR} -> ${CMAKE_BINARY_DIR}/${ENGINE_ASSETS_FOLDER}")
