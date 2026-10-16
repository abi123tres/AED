cmake_minimum_required(VERSION 4.0)
project(AED)

set(CMAKE_CXX_STANDARD 23)

add_executable(AED main.cpp
        "Contar frecuencias.cpp"
        Basico.cpp
        stringHash.cpp
        "Elementos distintos.cpp"
        "Multiset Iguales.cpp"
        "Sumar dos.cpp"
        "Primero no repetido.cpp"
        "Intersección de arreglos.cpp"
        "Simulador de diccionario.cpp"
        "Agrupando anagramas.cpp"
        Boyer-Moore.cpp
        "suma xor.cpp"
        "suma igualada.cpp"
        "es un avl.cpp"
        "alturas en un avl.cpp"
        "rotaciones a mano.cpp"
        AVL.cpp
        basico_avl.cpp
        "construir un avl.cpp"
        "contar rotaciones.cpp"
        ../../Downloads/rotaciones_a_mano.cpp
        "vecino mas cercano.cpp"
        "contar en rango.cpp")
