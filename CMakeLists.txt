cmake_minimum_required(VERSION 3.25)

project(perf_hw_1)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 6ea2dec23c3df14ac3b27b7d2d6bbff0cb7ba1b0)
FetchContent_MakeAvailable(cpr)

add_executable(perf_hw_1 main.cpp)
target_link_libraries(perf_hw_1 PRIVATE cpr::cpr)