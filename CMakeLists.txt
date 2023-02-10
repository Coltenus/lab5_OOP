cmake_minimum_required(VERSION 3.24)
project(lab5)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp src/Element.cpp src/Element.h src/common.h src/Circle.cpp src/Circle.h src/Rectangle.cpp src/Rectangle.h src/Group.cpp src/Group.h)

include(libs/CMakeLists.txt)
if(WIN32)
set(NO_CONSOLE_FLAG
        $<$<CONFIG:RELEASE>:-mwindows>)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${NO_CONSOLE_FLAG})
