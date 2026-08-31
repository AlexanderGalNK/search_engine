cmake_minimum_required(VERSION 4.0)
project(final_project_C__)

set(CMAKE_CXX_STANDARD 20)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(final_project_C__ main.cpp
        source/configClass.cpp
        header/configClass.h
        source/requestClass.cpp
        header/requestClass.h
)

target_link_libraries(final_project_C__ PRIVATE nlohmann_json::nlohmann_json)