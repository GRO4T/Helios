cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)

project(game-engine)

if (UNIX)
    if (POLICY CMP0072)
        cmake_policy(SET CMP0072 NEW)
    endif ()
    find_package(OpenGL REQUIRED)
    set(LIBS glfw GLEW)
    message(STATUS "Compiling for Linux 64bit")
elseif (WIN32)
    add_link_options(/NODEFAULTLIB:LIBCMT) # https://stackoverflow.com/questions/3007312/resolving-lnk4098-defaultlib-msvcrt-conflicts-with

    find_package(OpenGL REQUIRED)

    if (NOT CMAKE_CL_64)
        message(STATUS "Cannot compile for Windows 32bit!")
    else ()
        include_directories(lib/win/64bit/include)

        link_directories(lib/win/64bit)

        if (${MSVC_TOOLSET_VERSION} EQUAL 141)      #= VS 2017 (15.0)
            link_directories(lib/win/64bit/glfw/lib-vc2017)
        endif ()
        if (${MSVC_TOOLSET_VERSION} EQUAL 142)      #= VS 2019
            link_directories(lib/win/64bit/glfw/lib-vc2019)
        endif ()

        message(STATUS "Compiling for Windows 64bit")
    endif ()
    set(LIBS glfw3 glew32s)
endif ()

include_directories(project/include)
include_directories(lib/common/include)

add_library(
        game-engine
        project/include/camera.hpp
        project/src/camera.cpp
        project/include/display_manager.hpp
        project/src/display_manager.cpp
        project/include/game_engine.hpp
        project/src/stb_image.cpp
        project/include/renderer/master_renderer.hpp
        project/src/renderer/master_renderer.cpp project/include/model/model.hpp project/include/model/primitive.hpp project/include/utils.hpp project/src/model/model.cpp project/src/model/primitive.cpp project/include/shader/shader_program.hpp project/src/shader/shader_program.cpp project/src/utils.cpp project/include/shader/entity_shader.hpp project/include/model/materialized_model.hpp project/include/texture/texture.hpp project/include/texture/texture_manager.hpp project/include/model/material.hpp project/src/texture/texture.cpp project/src/texture/texture_manager.cpp project/include/entity/entity.hpp project/include/entity/abstract_entity.hpp project/include/renderer/entity_renderer.hpp project/src/renderer/entity_renderer.cpp)

target_link_libraries(game-engine OpenGL::GL ${LIBS})

add_executable(sandbox project/src/main.cpp)
target_link_libraries(sandbox game-engine)

# copy /res folder
add_custom_command(TARGET game-engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        $<TARGET_FILE_DIR:game-engine>/res
        )

# copy /res to /build (for running from Visual Studio)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_SOURCE_DIR}/build/res)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_SOURCE_DIR}/build/tests/res)
