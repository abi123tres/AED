#include <iostream>
#include <string>

using namespace std;

struct Nodo {
    string clave;
    int valor;
    Nodo* sig;
    Nodo(string c, int v) : clave(c), valor(v), sig(nullptr) {}
};

class Diccionario {
private:
    Nodo** tabla; // Arreglo dinámico de punteros a Nodo
    int m;        // Capacidad de la tabla (número de buckets)
    int n;        // Cantidad de elementos guardados actualmente

    int hash_func(string clave) {
        long long h = 0;
        long long B = 131;
        for (char c : clave) {
            h = (h * B + c) % m;
        }
        return h;
    }

public:
    // Constructor: crea el arreglo con m cajones vacíos
    Diccionario(int capacidad) {
        m = capacidad;
        n = 0;
        tabla = new Nodo*[m];
        for (int i = 0; i < m; ++i) {
            tabla[i] = nullptr;
        }
    }

    // Calcula el factor de carga actual: alpha = n / m
    double factor_carga() {
        return (double)n / m;
    }
    void contar_palabra(string palabra) {
        int idx = hash_func(palabra); // 1. Ya no pasas M como argumento
        Nodo* actual = tabla[idx];

        while (actual != nullptr) {
            if (actual->clave == palabra) {
                actual->valor++;
                return; // Ya existía: solo sumó 1 al valor y sale
            }
            actual = actual->sig;
        }

        // Si llegó aquí, es una palabra completamente nueva:
        Nodo* nuevo = new Nodo(palabra, 1);
        nuevo->sig = tabla[idx];
        tabla[idx] = nuevo;

        n++; // 2. ¡OJO AQUÍ! Incrementamos el total de claves guardadas
    }
    ~Diccionario() {
        for (int i = 0; i < m; ++i) {
            Nodo* actual = tabla[i];
            while (actual != nullptr) {
                Nodo* temp = actual;
                actual = actual->sig;
                delete temp;
            }
        }
        delete[] tabla;
    }
};
