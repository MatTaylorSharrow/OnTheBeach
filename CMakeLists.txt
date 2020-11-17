cmake_minimum_required(VERSION 3.5)

project(OnTheBeach LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(OTBLibrary/)
add_subdirectory(tsortcli/)
add_subdirectory(tests/)
