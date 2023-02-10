cmake_minimum_required(VERSION 3.24)

find_package(raylib REQUIRED)
include_directories(${CMAKE_PROJECT_NAME} ${raylib_INCLUDE_DIRS})
if(NOT raylib_FOUND)
    include(FetchContent)

    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git)
    FetchContent_MakeAvailable(raylib)
endif()

set(IMGUI_LIBRARIES ${raylib_LIBRARIES})

add_library(imgui STATIC
        ${CMAKE_CURRENT_LIST_DIR}/src/imconfig.h
        ${CMAKE_CURRENT_LIST_DIR}/src/imgui.h
        ${CMAKE_CURRENT_LIST_DIR}/src/imgui_internal.h
        ${CMAKE_CURRENT_LIST_DIR}/src/imstb_truetype.h
        ${CMAKE_CURRENT_LIST_DIR}/src/imstb_textedit.h
        ${CMAKE_CURRENT_LIST_DIR}/src/imstb_rectpack.h
        ${CMAKE_CURRENT_LIST_DIR}/src/rlImGui.h
        ${CMAKE_CURRENT_LIST_DIR}/src/rlImGuiColors.h
        ${CMAKE_CURRENT_LIST_DIR}/imgui_setup.h)

target_sources(imgui PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/imgui.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/imgui_demo.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/imgui_draw.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/imgui_tables.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/imgui_widgets.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/rlImGui.cpp
        ${CMAKE_CURRENT_LIST_DIR}/imgui_setup.cpp)

file(GLOB DLLS ${CMAKE_CURRENT_LIST_DIR}/*.dll)
file(COPY ${DLLS} DESTINATION ".")

target_link_libraries(imgui PRIVATE ${IMGUI_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE imgui)