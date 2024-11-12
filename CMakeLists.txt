cmake_minimum_required(VERSION 3.10)
project(UrbanMotion)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG origin/master
)
FetchContent_MakeAvailable(stb)

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${stb_SOURCE_DIR})
target_compile_definitions(stb_image INTERFACE STB_IMAGE_IMPLEMENTATION)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.89.2
)
FetchContent_MakeAvailable(imgui)

set(IMGUI_SOURCES
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

find_package(OpenGL REQUIRED)

add_executable(UrbanMotion
    main.cpp
    src/imgui/Manager.cpp
    src/imgui/Window.cpp
    src/imgui/Panel.cpp
    src/components/Map.cpp
    src/components/Field.cpp
    src/filestorage/Handler.cpp
    src/filestorage/MapFile.cpp
    src/filestorage/mapper.cpp
    src/texture/Manager.cpp
    src/App.cpp
    ${IMGUI_SOURCES}
)

target_include_directories(UrbanMotion PRIVATE 
    ${imgui_SOURCE_DIR} 
    ${imgui_SOURCE_DIR}/backends 
    ${glad_SOURCE_DIR}/include
    ${stb_SOURCE_DIR}
)

target_compile_definitions(UrbanMotion PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_link_libraries(UrbanMotion PRIVATE glfw OpenGL::GL stb_image)
