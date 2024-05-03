cmake_minimum_required(VERSION 3.28)
project(DA_project_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA_project_2 src/main.cpp
        src/Haversine.h
        src/Haversine.cpp
        src/data_structures/Graph.h
        src/data_structures/Graph.cpp
        src/data_structures/Edge.cpp
        src/data_structures/Edge.h
        src/data_structures/Vertex.cpp
        src/data_structures/Vertex.h
        src/Interface.cpp
        src/Interface.h
        src/TSPManager.cpp
        src/TSPManager.h
        src/Coordinate.cpp
        src/Coordinate.h)
