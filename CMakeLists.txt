cmake_minimum_required(VERSION 4.0)
project(AED)

set(CMAKE_CXX_STANDARD 23)

add_executable(AED main.cpp
        "Contar frecuencias.cpp"
        Basico.cpp
        stringHash.cpp
        "Elementos distintos.cpp"
        "Multiset Iguales.cpp")
