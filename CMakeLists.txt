cmake_minimum_required(VERSION 3.6)
project(Chip8-Emu)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Chip8-Emu_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp system.cpp cpu.cpp gfx.cpp)
add_executable(Chip8-Emu ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

find_package(SDL2 REQUIRED)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${Chip8-Emu_SOURCE_DIR}/source/headers)

target_link_libraries(Chip8-Emu ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})