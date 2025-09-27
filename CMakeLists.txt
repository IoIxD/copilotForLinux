cmake_minimum_required(VERSION 3.20)
project(copilotForLinux LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig)
pkg_check_modules(GTK REQUIRED gtk4)
pkg_check_modules(WebkitGTK REQUIRED webkitgtk-6.0)

include_directories(${GTK_INCLUDE_DIRS})
link_libraries(${GTK_LIBRARIES})
include_directories(${WebkitGTK_INCLUDE_DIRS})
link_libraries(${WebkitGTK_LIBRARIES})

FILE(GLOB_RECURSE sources src/*.c)

add_executable(${PROJECT_NAME} ${sources})
