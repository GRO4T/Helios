cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

project(HeliosCore)

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

include_directories(Helios/Core/include)
include_directories(lib/common/include)

add_library(
        HeliosCore
        Helios/Core/include/camera.hpp
        Helios/Core/src/camera.cpp
        Helios/Core/include/display_manager.hpp
        Helios/Core/src/display_manager.cpp
        Helios/Core/include/game_engine.hpp
        Helios/Core/src/stb_image.cpp
        Helios/Core/include/renderer/master_renderer.hpp
        Helios/Core/src/renderer/master_renderer.cpp
        Helios/Core/include/model/mesh.hpp
        Helios/Core/include/model/primitive_mesh.hpp
        Helios/Core/include/utils.hpp
        Helios/Core/src/model/mesh.cpp
        Helios/Core/src/model/primitive_mesh.cpp
        Helios/Core/include/shader/shader_program.hpp
        Helios/Core/src/shader/shader_program.cpp
        Helios/Core/src/utils.cpp
        Helios/Core/include/shader/entity_shader.hpp
        Helios/Core/include/model/materialized_mesh.hpp
        Helios/Core/include/texture/texture.hpp
        Helios/Core/include/texture/texture_manager.hpp
        Helios/Core/include/model/material.hpp
        Helios/Core/src/texture/texture_manager.cpp
        Helios/Core/include/entity.hpp
        Helios/Core/include/transformable.hpp
        Helios/Core/include/renderer/entity_renderer.hpp
        Helios/Core/src/renderer/entity_renderer.cpp
        Helios/Core/include/renderer/light_renderer.hpp
        Helios/Core/include/shader/light_shader.hpp
        Helios/Core/include/light.hpp
        Helios/Core/include/model/model.hpp
        Helios/Core/src/model/model.cpp
)

target_link_libraries(HeliosCore OpenGL::GL ${LIBS})

add_executable(Sandbox Helios/Core/src/main.cpp)
target_link_libraries(Sandbox HeliosCore)

# copy /res folder
add_custom_command(TARGET HeliosCore POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        $<TARGET_FILE_DIR:HeliosCore>/res
        )

# copy dlls
if (WIN32)
    add_custom_command(TARGET HeliosCore POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/dll
            $<TARGET_FILE_DIR:HeliosCore>
            )
endif ()

# copy /res to /build (for running from Visual Studio)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_SOURCE_DIR}/build/res)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_SOURCE_DIR}/build/tests/res)
