cmake_minimum_required(VERSION 3.16)
project(Aetherbound CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Path to raylib
set(RAYLIB_PATH "${CMAKE_SOURCE_DIR}/../../temp/raylib")

include_directories(${RAYLIB_PATH}/src)

add_executable(${PROJECT_NAME} src/main.cpp)

if(EXISTS "${RAYLIB_PATH}/build/raylib/libraylib.a")
    set(RAYLIB_LIB "${RAYLIB_PATH}/build/raylib/libraylib.a")
elseif(EXISTS "${RAYLIB_PATH}/src/libraylib.a")
    set(RAYLIB_LIB "${RAYLIB_PATH}/src/libraylib.a")
else()
    message(FATAL_ERROR "raylib static library not found. Please build raylib first.")
endif()

target_link_libraries(${PROJECT_NAME}
    ${RAYLIB_LIB}
    "-framework CoreVideo"
    "-framework IOKit"
    "-framework Cocoa"
    "-framework GLUT"
    "-framework OpenGL"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")