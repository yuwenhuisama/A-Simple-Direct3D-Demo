cmake_minimum_required(VERSION 3.15.0)
project(DirectX11Task VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

FIND_PACKAGE(RapidJSON CONFIG REQUIRED)

# ADD_DEFINITIONS("-D_ENABLE_EXTENDED_ALIGNED_STORAGE")

SET(DIRECTX_DEPENDENCIES 
    dxgi.lib; Windowscodecs.lib; d3d10_1.lib; d3d11.lib;
    d2d1.lib; dxguid.lib; D3DCompiler.lib; Winmm.lib; Dwrite.lib
    dinput8.lib dxguid.lib)

FOREACH(LIB ${DIRECTX_DEPENDENCIES})
    FIND_LIBRARY(FOUND_LIB_${LIB} ${LIB})
    link_libraries(${FOUND_LIB_${LIB}})
ENDFOREACH (LIB)

FIND_LIBRARY(DIRECTXTEX_LIB DirectXTex.lib)
link_libraries(${DIRECTXTEX_LIB})

include(CTest)
enable_testing()

include_directories(./)

aux_source_directory(./DxUtils SRC_DXUTILS)
aux_source_directory(./DxUtils/Shaders SRC_DXUTILS_SHADERS)
aux_source_directory(./DxUtils/Shaders/Effect SRC_DXUTILS_SHADERS_EFFECT)
aux_source_directory(./DxUtils/RenderCommandQueue SRC_DXUTILS_RENDERCOMMANDQUEUE)
aux_source_directory(./GameObjects SRC_GAMEOBJECTS)
aux_source_directory(./GameObjects/BasicShapes SRC_GAMEOBJECTS_BASICSHAPES)
aux_source_directory(./GameObjects/JsonObjects SRC_GAMEOBJECTS_JSONOBJECTS)
aux_source_directory(./GameScenes SRC_GAMESCENES)
aux_source_directory(./GameUtils SRC_GAMEUTILS)
aux_source_directory(./GameControllers SRC_GAMECONTROLLERS)
aux_source_directory(./DxUtils/WicTextureLoader SRC_DXUTILS_WICTEXTURELOADER)

add_executable(DirectX11Task
    WIN32
    main.cpp
    ${SRC_DXUTILS}
    ${SRC_DXUTILS_WICTEXTURELOADER}
    ${SRC_DXUTILS_SHADERS}
    ${SRC_DXUTILS_SHADERS_EFFECT}
    ${SRC_DXUTILS_RENDERCOMMANDQUEUE}
    ${SRC_GAMEOBJECTS}
    ${SRC_GAMEOBJECTS_BASICSHAPES}
    ${SRC_GAMEOBJECTS_JSONOBJECTS}
    ${SRC_GAMESCENES}
    ${SRC_GAMEUTILS}
    ${SRC_GAMECONTROLLERS})

target_include_directories(DirectX11Task PRIVATE ${RAPIDJSON_INCLUDE_DIRS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
