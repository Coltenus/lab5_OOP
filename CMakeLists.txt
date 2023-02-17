cmake_minimum_required(VERSION 3.24)
project(lab5)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp src/Elements/Element.cpp src/Elements/Element.h src/common.h src/Elements/Circle.cpp src/Elements/Circle.h src/Elements/Rectangle.cpp src/Elements/Rectangle.h src/Elements/Group.cpp src/Elements/Group.h src/Window.cpp src/Window.h src/Elements/elements.h src/Menu.cpp src/Menu.h src/MenuObjects/MenuObject.h src/MenuObjects/LabelMO.h src/MenuObjects/ButtonMO.h src/MenuObjects/mobjects.h src/MenuObjects/PreviewMO.cpp src/MenuObjects/PreviewMO.h src/Commands/ButtonCommand.h src/Commands/ValueSetBC.h src/Commands/bcommands.h src/MenuObjects/ButtonMO.cpp src/FigureBuilder.cpp src/FigureBuilder.h src/MenuObjects/LabelMO.cpp src/MenuObjects/EditorMO.cpp src/MenuObjects/EditorMO.h src/MenuObjects/SliderMO.h src/Commands/SliderCommand.h src/MenuObjects/SliderMO.cpp)

find_package(raylib REQUIRED)
if(NOT raylib_FOUND)
    include(FetchContent)

    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git)
    FetchContent_MakeAvailable(raylib)
endif()
include_directories(${CMAKE_PROJECT_NAME} ${raylib_INCLUDE_DIRS})
if(WIN32)
set(NO_CONSOLE_FLAG
        $<$<CONFIG:RELEASE>:-mwindows>)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${raylib_LIBRARIES} ${NO_CONSOLE_FLAG})
