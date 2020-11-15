cmake_minimum_required(VERSION 3.14)

project(OTBLibrary LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(OTBLibrary SHARED
  OTBLibrary_global.h
  otblibrary.cpp
  otblibrary.h
)

target_compile_definitions(OTBLibrary PRIVATE OTBLIBRARY_LIBRARY)
