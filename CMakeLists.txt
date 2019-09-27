cmake_minimum_required(VERSION 2.8.12)
project(RealmWar)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(RESOURCE_PATH ${PROJECT_SOURCE_DIR})

configure_file (
  "${PROJECT_SOURCE_DIR}/include/config.h.in"
  "${PROJECT_SOURCE_DIR}/include/config.h"
  )

include_directories("include")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} src/main.cpp src/inputHandler.cpp src/Mushroom.cpp src/enemy.cpp src/tile.cpp src/map.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})