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
        source/SearchServer.cpp
        header/SearchServer.h
)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
)
include_directories(${gtest_SOURCE_DIR}/include${gtest_SOURCE_DIR})
set(gtest_disable_pthreads)

FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(sample_test source/test.cpp
        #header/InvertedIndex.h)
        source/InvertedIndex.cpp)

target_link_libraries(sample_test PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(search_engine)

