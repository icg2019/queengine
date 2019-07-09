cmake_minimum_required(VERSION 3.0.2)

project(openglexample LANGUAGES CXX)
set(GAME_NAME openglexample)

option(RELEASE_BUILD "Release build" OFF)

if (RELEASE_BUILD)
    message("== Release BUILD ==")
    set(GAME_RESOURCES_FOLDER "/usr/games/${GAME_NAME}-resources")
else()
    message("== Debug BUILD ==")
    set(GAME_RESOURCES_FOLDER "game")
endif()

set(GAME_ASSETS_FOLDER "${GAME_RESOURCES_FOLDER}/assets")

set (PROJECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/game/include")
set (PROJECT_SRC_DIR     "${PROJECT_SOURCE_DIR}/game/src")
set (PROJECT_LIBS_DIR    "${PROJECT_SOURCE_DIR}/libs")
set (PROJECT_ASSETS_DIR  "${PROJECT_SOURCE_DIR}/game/assets")

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
    set(COMPILE_FLAGS "${COMPILE_FLAGS} -std=c++11 -W -Wall -pedantic -Wshadow -g")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    set(COMPILE_FLAGS "${COMPILE_FLAGS} -std=c++11 -W -Wall -pedantic -Wshadow -g")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(COMPILE_FLAGS "${COMPILE_FLAGS} /Wall")
endif()



# GLFW
add_subdirectory("${PROJECT_LIBS_DIR}/glfw")
include_directories("${PROJECT_LIBS_DIR}/glfw/include")

# GLAD
add_subdirectory("${PROJECT_LIBS_DIR}/glad")
include_directories("${PROJECT_LIBS_DIR}/glad/include")

# STB
include_directories("${PROJECT_LIBS_DIR}/stb")

find_package(ASSIMP REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIR})


## Executable

add_executable(${GAME_NAME} ${SOURCES})
target_link_libraries(${GAME_NAME} glfw glad ${ASSIMP_LIBRARY})


#### Custom Commands ####

# Copy assets folder to build
add_custom_command(TARGET ${GAME_NAME} PRE_BUILD
   COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/game"
   COMMENT "mkdir ${CMAKE_BINARY_DIR}/game")
add_custom_command(TARGET ${GAME_NAME} PRE_BUILD
   COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_ASSETS_DIR} "${CMAKE_BINARY_DIR}/${GAME_ASSETS_FOLDER}"
   COMMENT "symlink ${PROJECT_ASSETS_DIR} -> ${CMAKE_BINARY_DIR}/${GAME_ASSETS_FOLDER}")
