cmake_minimum_required(VERSION 3.5)

project(tsortcli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tsortcli main.cpp)
target_link_libraries(tsortcli PRIVATE OTBLibrary)
target_link_directories(tsortcli PRIVATE "../build/OTBLibrary/Debug/")
