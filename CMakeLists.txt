cmake_minimum_required(VERSION 3.16)
project(Algorithm LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Algorithm source/tictactoe.cpp)

target_include_directories(Algorithm PRIVATE ${CMAKE_SOURCE_DIR}/source ${CMAKE_SOURCE_DIR}/lib)

# Link libraries
target_link_libraries(Algorithm
    ${CMAKE_SOURCE_DIR}/lib/libraylib.a
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)