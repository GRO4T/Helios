cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

project(game-engine)

if (UNIX)
    if (POLICY CMP0072)
        cmake_policy(SET CMP0072 NEW)
    endif ()
    find_package(OpenGL REQUIRED)
    set(LIBS glfw GLEW assimp)
    message(STATUS "Compiling for Linux 64bit")
elseif (WIN32)
    add_link_options(/NODEFAULTLIB:LIBCMT) # https://stackoverflow.com/questions/3007312/resolving-lnk4098-defaultlib-msvcrt-conflicts-with

    find_package(OpenGL REQUIRED)

    if (NOT CMAKE_CL_64)
        message(FATAL_ERROR "Cannot compile for Windows 32bit!")
    else ()
        include_directories(lib/win/64bit/include)

        link_directories(lib/win/64bit)
        link_directories(lib/win/64bit/glfw/lib-vc2019)

        message(STATUS "Compiling for Windows 64bit")
    endif ()
    set(LIBS glfw3 glew32s assimp-vc142-mt)
endif ()

include_directories(include)
include_directories(lib/common/include)

add_library(
        game-engine
        include/camera.hpp
        src/camera.cpp
        include/display_manager.hpp
        src/display_manager.cpp
        include/game_engine.hpp
        src/stb_image.cpp
        include/renderer/master_renderer.hpp
        src/renderer/master_renderer.cpp
        include/model/mesh.hpp
        include/model/primitive_mesh.hpp
        include/utils.hpp
        src/model/mesh.cpp
        src/model/primitive_mesh.cpp
        include/shader/shader_program.hpp
        src/shader/shader_program.cpp
        src/utils.cpp
        include/shader/entity_shader.hpp
        include/model/materialized_mesh.hpp
        include/texture/texture.hpp
        include/texture/texture_manager.hpp
        include/model/material.hpp
        src/texture/texture_manager.cpp
        include/entity.hpp include/transformable.hpp
        include/renderer/entity_renderer.hpp
        src/renderer/entity_renderer.cpp
        include/renderer/light_renderer.hpp
        include/shader/light_shader.hpp
        include/light.hpp
        include/model/model.hpp
        src/model/model.cpp
)

target_link_libraries(game-engine OpenGL::GL ${LIBS})

add_executable(sandbox src/main.cpp)
target_link_libraries(sandbox game-engine)

# copy /res folder
add_custom_command(TARGET game-engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        $<TARGET_FILE_DIR:game-engine>/res
        )

# copy dlls
if (WIN32)
    add_custom_command(TARGET game-engine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/dll
            $<TARGET_FILE_DIR:game-engine>
            )
endif ()

# copy /res to /build (for running from Visual Studio)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_SOURCE_DIR}/build/res)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_SOURCE_DIR}/build/tests/res)
