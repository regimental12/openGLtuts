cmake_minimum_required(VERSION 2.8.4)
project(openGL)

set(SOURCE_FILES main.cpp)
add_executable(openGL ${SOURCE_FILES})

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})