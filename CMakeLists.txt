
cmake_minimum_required(VERSION 3.11)

project(nonogrammer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQIRED ON)

add_compile_options(
    -Werror
    -Wall
    -Wunreachable-code
)

add_subdirectory(nngr)
add_subdirectory(testing)

find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(nonogrammer main.cpp)

target_link_libraries(nonogrammer
    PRIVATE nngr
    PRIVATE nlohmann_json::nlohmann_json
)
