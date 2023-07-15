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
        Helios/Core/include/Camera.hpp
        Helios/Core/src/Camera.cpp
        Helios/Core/include/DisplayManager.hpp
        Helios/Core/src/DisplayManager.cpp
        Helios/Core/include/GameEngine.hpp
        Helios/Core/src/stb_image.cpp
        Helios/Core/include/renderer/MasterRenderer.hpp
        Helios/Core/src/renderer/MasterRenderer.cpp
        Helios/Core/include/model/Mesh.hpp
        Helios/Core/include/model/PrimitiveMesh.hpp
        Helios/Core/include/Utils.hpp
        Helios/Core/src/model/Mesh.cpp
        Helios/Core/src/model/PrimitiveMesh.cpp
        Helios/Core/include/shader/ShaderProgram.hpp
        Helios/Core/src/shader/ShaderProgram.cpp
        Helios/Core/src/Utils.cpp
        Helios/Core/include/shader/EntityShader.hpp
        Helios/Core/include/model/MaterializedMesh.hpp
        Helios/Core/include/texture/Texture.hpp
        Helios/Core/include/texture/TextureManager.hpp
        Helios/Core/include/model/Material.hpp
        Helios/Core/src/texture/TextureManager.cpp
        Helios/Core/include/Entity.hpp
        Helios/Core/include/Transformable.hpp
        Helios/Core/include/renderer/EntityRenderer.hpp
        Helios/Core/src/renderer/EntityRenderer.cpp
        Helios/Core/include/renderer/LightRenderer.hpp
        Helios/Core/include/shader/LightShader.hpp
        Helios/Core/include/Light.hpp
        Helios/Core/include/model/Model.hpp
        Helios/Core/src/model/Model.cpp
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
