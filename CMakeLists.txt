set(CMAKE_CXX_STANDARD 26)
cmake_minimum_required(VERSION 3.31)
project(CommandLineInjector)

file(GLOB_RECURSE sourceFiles "Src/*.cpp")
file(GLOB_RECURSE includeFiles "Src/*.hpp")
set_source_files_properties(${sourceFiles} PROPERTIES CXX_SCAN_FOR_MODULES OFF)
set_source_files_properties(${includeFiles} PROPERTIES CXX_SCAN_FOR_MODULES OFF)

include_directories(.)

add_executable(CommandLineInjector ${sourceFiles} ${resource_files})