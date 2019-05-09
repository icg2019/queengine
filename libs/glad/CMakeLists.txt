cmake_minimum_required(VERSION 3.0.2)
project (GLAD LANGUAGES C)

set (GLAD_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")
set (GLAD_SRC_DIR      "${PROJECT_SOURCE_DIR}/src")

file(GLOB_RECURSE SOURCES "${GLAD_SRC_DIR}/*.c")

include_directories("${GLAD_INCLUDE_DIRS}")

add_library(glad STATIC ${SOURCES})
