cmake_minimum_required(VERSION 4.0)
project(search_engine)

set(CMAKE_CXX_STANDARD 20)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(search_engine main.cpp
        source/ConverterJSON.cpp
        header/ConverterJSON.h
        header/InvertedIndex.h
        source/InvertedIndex.cpp
        header/main.h
)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)