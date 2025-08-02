cmake_minimum_required(VERSION 3.16)
project(Aetherbound CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/embed_resources.cmake)
add_executable(${PROJECT_NAME} src/main.cpp)
add_embedded_resources(${PROJECT_NAME})

if(WIN32)
    set(RAYLIB_INCLUDE_DIR "C:/RaylibSDK/include")
    set(RAYLIB_LIB_DIR "C:/RaylibSDK/lib")

    include_directories(${RAYLIB_INCLUDE_DIR})
    link_directories(${RAYLIB_LIB_DIR})

    target_link_libraries(${PROJECT_NAME}
        "${RAYLIB_LIB_DIR}/raylib.lib"
        opengl32
        gdi32
        winmm
    )

elseif(APPLE)
    set(RAYLIB_PATH "${CMAKE_SOURCE_DIR}/../../temp/raylib")
    include_directories(${RAYLIB_PATH}/src)

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

else()
    message(FATAL_ERROR "Unsupported platform.")
endif()