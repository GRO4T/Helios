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

include_directories(include)
include_directories(lib/common/include)

add_library(
        HeliosCore
        include/Helios/Core/Camera.hpp
        include/Helios/Core/DisplayManager.hpp
        include/Helios/Core/Entity.hpp
        include/Helios/Core/Light.hpp
        include/Helios/Core/Transformable.hpp
        include/Helios/Core/Utils.hpp
        include/Helios/Core/model/Material.hpp
        include/Helios/Core/model/MaterializedMesh.hpp
        include/Helios/Core/model/Mesh.hpp
        include/Helios/Core/model/Model.hpp
        include/Helios/Core/model/PrimitiveMesh.hpp
        include/Helios/Core/renderer/EntityRenderer.hpp
        include/Helios/Core/renderer/LightRenderer.hpp
        include/Helios/Core/renderer/MasterRenderer.hpp
        include/Helios/Core/shader/EntityShader.hpp
        include/Helios/Core/shader/LightShader.hpp
        include/Helios/Core/shader/ShaderProgram.hpp
        include/Helios/Core/texture/Texture.hpp
        include/Helios/Core/texture/TextureManager.hpp
        src/Helios/Core/Camera.cpp
        src/Helios/Core/DisplayManager.cpp
        src/Helios/Core/GameEngine.cpp
        src/Helios/Core/Utils.cpp
        src/Helios/Core/model/Mesh.cpp
        src/Helios/Core/model/Model.cpp
        src/Helios/Core/model/PrimitiveMesh.cpp
        src/Helios/Core/renderer/EntityRenderer.cpp
        src/Helios/Core/renderer/MasterRenderer.cpp
        src/Helios/Core/shader/ShaderProgram.cpp
        src/Helios/Core/stb_image.cpp
        src/Helios/Core/texture/TextureManager.cpp
)

target_link_libraries(HeliosCore OpenGL::GL ${LIBS})

add_executable(Sandbox examples/Sandbox/main.cpp)
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
