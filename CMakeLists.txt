cmake_minimum_required(VERSION 3.17)
project(e_estafetas)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Build GraphViewerCpp
set(GRAPHVIEWERCPP_PATH lib/GraphViewerCpp)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)


add_executable(e_estafetas
        main.cpp
        Company.h
        Car.h
        Request.h
        Client.h
        Store.h
        utils.h
        Graph.h
        MutablePriorityQueue.h
        Connectivity.h Algorithms.h Time.h)


target_link_libraries(e_estafetas graphviewer)