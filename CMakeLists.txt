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

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

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
    src/imgui/GameScreen.cpp
    src/imgui/DropTargetWindow.cpp
    src/imgui/WelcomeScreen.cpp
    src/imgui/RotationTransform.cpp
    src/imgui/GameScreen.cpp
    src/imgui/OpenGLScreenshotHandler.cpp
    src/components/Map.cpp
    src/components/ListOfVehicle.cpp
    src/components/Fields.cpp
    src/movement/Strategy.cpp
    src/movement/Controller.cpp
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
    ${glfw_SOURCE_DIR}/include
)

target_compile_definitions(UrbanMotion PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_link_libraries(UrbanMotion PRIVATE glfw OpenGL::GL stb_image glm)

enable_testing()

add_executable(ListOfVehicleTest
    tests/ListOfVehicleTest.cpp
    src/components/ListOfVehicle.cpp
    src/components/Fields.cpp
)
target_include_directories(ListOfVehicleTest PRIVATE 
    ${imgui_SOURCE_DIR} 
    ${imgui_SOURCE_DIR}/backends 
    ${glad_SOURCE_DIR}/include
    ${stb_SOURCE_DIR}
    ${glfw_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/tests
    ${googletest_SOURCE_DIR}/include
    ${googletest_BINARY_DIR}
)
target_link_libraries(ListOfVehicleTest gtest_main gmock_main glfw OpenGL::GL stb_image glm)

add_executable(FieldsTest
    tests/FieldsTest.cpp
    src/components/Fields.cpp
)
target_include_directories(FieldsTest PRIVATE 
    ${imgui_SOURCE_DIR} 
    ${imgui_SOURCE_DIR}/backends 
    ${glad_SOURCE_DIR}/include
    ${stb_SOURCE_DIR}
    ${glfw_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/tests
    ${googletest_SOURCE_DIR}/include
    ${googletest_BINARY_DIR}
)

target_link_libraries(FieldsTest gtest_main gmock_main glfw OpenGL::GL stb_image glm)

include(GoogleTest)
gtest_discover_tests(ListOfVehicleTest)
gtest_discover_tests(FieldsTest)
