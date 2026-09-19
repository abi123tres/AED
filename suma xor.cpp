#include <iostream>
using namespace std;

struct Nodo {
    int clave;
    Nodo* sig;
    Nodo(int c) : clave(c), sig(nullptr) {}
};

// 2. La tabla de buckets (iniciada en nullptr)
const int M = 1000003;
Nodo* tabla[M] = {nullptr};

// 3. Función hash por división
int hash_func(int clave) {
    return ((clave % M) + M) % M; // Maneja enteros positivos y negativos
}


bool buscar(int clave) {
  int idx = hash_func(clave);
  Nodo* actual = tabla[idx];
  while (actual != nullptr) {
   if (actual->clave == clave) {
    return true;
   }
   actual = actual->sig;
  }
  return false;
}

bool insertar(int clave) {
 int idx = hash_func(clave);
 Nodo* nuevo = new Nodo(clave);
 nuevo->sig = tabla[idx];
 tabla[idx] = nuevo;
}


int main() {
 ios_base::sync_with_stdio(false);
 cin.tie(nullptr);

 int n;
 if (!(cin >> n)) return 0;

 for (int i = 0; i < n; i++) {
  int a_i;
  cin >> a_i;
 }

}

/*Se te da un arreglo de n
 enteros a1,…,an
 y un entero X
 (el valor objetivo). Determina si existen dos índices distintos i≠j
 tales que ai⊕aj=X
, donde ⊕
 denota la operación XOR bit a bit.

Input
La primera línea contiene dos enteros n
 y X
 (1≤n≤106
, 0≤X≤109
). La segunda línea contiene n
 enteros a1,…,an
 (0≤ai≤109
): el arreglo.

Output
Imprime SI si existen dos índices distintos i≠j
 con ai⊕aj=X
, o NO en caso contrario.

Scoring
Límites

Este problema tiene subtareas, por lo cual es posible obtener un puntaje en base a las subtareas que logren ser resueltas.

1≤n≤106
0≤ai≤109
 para todo i=1,…,n
.
0≤X≤109
Grupo 1 (1 punto)

n≤2
Grupo 2 (1 punto)

n≤2000
Grupo 3 (2 puntos)

Sin restricciones adicionales.
Example
InputCopy
6 6
3 7 10 1 9 12
OutputCopy
SI
Note
Con n=6
, X=6
 y a=[3,7,10,1,9,12]
: recorriendo el arreglo de izquierda a derecha y guardando los valores ya vistos, al llegar a a4=1
 se calcula a4⊕X=00012⊕01102=01112=7
, y 7
 ya había aparecido antes (es a2
), así que los índices i=2
, j=4
 cumplen a2⊕a4=01112⊕00012=01102=6=X
 y la respuesta es SI.

Esto funciona porque a⊕b=X⟺a⊕X=b
 (el XOR es su propio inverso), lo que da la misma forma de "buscar el complemento en un conjunto de vistos" que un problema de suma de dos términos, pero con XOR en vez de resta. Un detalle importante: si X=0
, entonces ai⊕X=ai
, así que revisar si ai
 ya fue visto antes de insertarlo es exactamente lo que se necesita para exigir una aparición distinta de ese mismo valor (dos posiciones con el mismo número, no una posición emparejada consigo misma).


*/








#include <iostream>

using namespace std;

struct Nodo {
 int clave;
 Nodo* sig;
 Nodo(int c) : clave(c), sig(nullptr) {}
};

// Tamaño de la tabla hash (un número primo superior a 10^6)
const int M = 2000003;
Nodo* tabla[M] = {nullptr};

// Función Hash para enteros
int hash_func(int clave) {
 return ((clave % M) + M) % M;
}

// Verifica si la clave ya existe en la tabla
bool buscar(int clave) {
 int idx = hash_func(clave);
 Nodo* actual = tabla[idx];
 while (actual != nullptr) {
  if (actual->clave == clave) {
   return true;
  }
  actual = actual->sig;
 }
 return false;
}

// Inserta una clave en la tabla Hash
void insertar(int clave) {
 int idx = hash_func(clave);
 Nodo* nuevo = new Nodo(clave);
 nuevo->sig = tabla[idx];
 tabla[idx] = nuevo;
}

int main() {
 // Optimización de I/O para evitar Time Limit Exceeded
 ios_base::sync_with_stdio(false);
 cin.tie(nullptr);

 int n, X;
 if (!(cin >> n >> X)) return 0;

 for (int i = 0; i < n; ++i) {
  int a_i;
  cin >> a_i;

  int objetivo = a_i ^ X; // a_i XOR X

  // 1. Verificar si el complemento necesario ya fue visto antes
  if (buscar(objetivo)) {
   cout << "SI\n";
   return 0;
  }

  // 2. Insertar el elemento actual en la tabla Hash
  insertar(a_i);
 }

 cout << "NO\n";
 return 0;
}