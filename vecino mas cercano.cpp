#include <iostream>
using namespace std;
template<typename data_type>
struct AVL {

    struct TreeNode {
        int height;
        data_type data;
        TreeNode* left;
        TreeNode* right;

        // Constructor por defecto
        TreeNode(data_type data = data_type(), int height = 0,
                    TreeNode* left = nullptr,
                    TreeNode* right = nullptr) :
                    data(data), height(height), left(left), right(right) {}
    };

    TreeNode* root;

    AVL() {
        root = nullptr;
    }

    // 1. Devuelve la altura de un nodo (si es nulo, retorna -1)[cite: 140, 157]
    int h(TreeNode* u) {
        return u == nullptr ? -1 : u -> height;
    }

    // 2. Actualiza la altura de un nodo basándose en la altura máxima de sus hijos[cite: 140, 158]
    void update(TreeNode* u) {
        u -> height = 1 + max(h(u -> left) , h(u -> right));
    }

    // 3. Calcula el Factor de Balance (FB = Altura Izquierda - Altura Derecha)[cite: 140, 159]
    int FB(TreeNode* u) {
        return h(u -> left) - h(u -> right);
    }

    TreeNode* rotate_left(TreeNode* u) {
        TreeNode* v = u -> right;
        u -> right = v -> left;
        v -> left = u;
        update(u); // Actualiza primero al que bajó
        update(v); // Actualiza después a la nueva raíz
        return v;  // Retorna la nueva raíz del subárbol
    }

    TreeNode* rotate_right(TreeNode* u) {
        TreeNode* v = u -> left;
        u -> left = v -> right;
        v -> right = u;
        update(u); // Actualiza primero al que bajó
        update(v); // Actualiza después a la nueva raíz
        return v;  // Retorna la nueva raíz del subárbol[cite: 140]
    }

    TreeNode* rebalance(TreeNode* u) {
        update(u); // Actualizamos la altura actual

        // Desbalance por la IZQUIERDA (FB > 1)[cite: 166]
        if (FB(u) > 1) {
            // Si el hijo izquierdo apunta hacia la derecha, es caso LR (rotación doble)[cite: 92, 140, 166]
            if (FB(u -> left) < 0) {
                u -> left = rotate_left(u -> left);
            }
            // Caso LL o LR resuelto: rotación a la derecha[cite: 92, 140, 166]
            return rotate_right(u);
        }

        // Desbalance por la DERECHA (FB < -1)[cite: 166]
        if (FB(u) < -1) {
            // Si el hijo derecho apunta hacia la izquierda, es caso RL (rotación doble)[cite: 92, 140, 166]
            if (FB(u -> right) > 0) {
                u -> right = rotate_right(u -> right);
            }
            // Caso RR o RL resuelto: rotación a la izquierda[cite: 92, 140, 166]
            return rotate_left(u);
        }

        return u; // Si ya estaba balanceado, retorna el nodo intacto[cite: 166]
    }
    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current -> left != nullptr) {
            current = current -> left;
        }
        return current; // El nodo más a la izquierda
    }

    // Retorna el nodo con la clave máxima a partir de un nodo 'u'
    TreeNode* max_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current -> right != nullptr) {
            current = current -> right;
        }
        return current; // El nodo más a la derecha
    }

    // Interfaz pública para el usuario (desde la raíz)
    TreeNode* min_element() {
        return min_element(root);
    }

    TreeNode* max_element() {
        return max_element(root);
    }
    TreeNode* insert(TreeNode* u, data_type value) {
        // 1. Caso base: encontramos el espacio vacío para insertar[cite: 140, 168]
        if (u == nullptr) {
            return new TreeNode(value, 0); // Nace con altura 0[cite: 140, 168]
        }

        // 2. Descenso recursivo en el BST[cite: 140, 168]
        if (value < u -> data) {
            u -> left = insert(u -> left, value);
        }
        else if (value > u -> data) {
            u -> right = insert(u -> right, value);
        }
        else {
            return u; // Elemento duplicado, no se inserta
        }

        // 3. Al regresar de la recursión, rebalanceamos cada ancestro[cite: 140, 168]
        return rebalance(u);
    }

    // Interfaz pública para el usuario[cite: 140]
    void insert(data_type value) {
        root = insert(root, value);
    }

    // Función auxiliar para encontrar el nodo que contiene una clave
    TreeNode* buscar_nodo(TreeNode* u, data_type val) {
        if (u == nullptr || u->data == val) {
            return u; // Si lo encuentra o llega a nulo, retorna el nodo (o nullptr)
        }
        if (val < u->data) {
            return buscar_nodo(u->left, val); // Busca por la izquierda
        }
        return buscar_nodo(u->right, val);     // Busca por la derecha
    }

    // Función recursiva privada para eliminar una clave
    TreeNode* erase(TreeNode* u, data_type val) {
        // 1. Caso base: si llegamos a un nodo nulo, la clave no está en el árbol
        if (u == nullptr) return nullptr;

        // 2. Descenso recursivo buscando la clave
        if (val < u -> data) {
            u -> left = erase(u -> left, val);
        }
        else if (val > u -> data) {
            u -> right = erase(u -> right, val);
        }
        else {
            // --- ¡ENCONTRAMOS EL NODO A ELIMINAR! ---

            // CASO A: Si no tiene hijo izquierdo, su hijo derecho toma su lugar
            if (u -> left == nullptr) {
                TreeNode* temp = u -> right;
                delete u;
                return temp;
            }
            // CASO B: Si no tiene hijo derecho, su hijo izquierdo toma su lugar
            else if (u -> right == nullptr) {
                TreeNode* temp = u -> left;
                delete u;
                return temp;
            }

            // CASO C: Si tiene ambos hijos, buscamos el sucesor
            // (el mínimo de su subárbol derecho)
            TreeNode* temp = min_element(u -> right);

            // Copiamos la clave del sucesor al nodo actual
            u -> data = temp -> data;

            // Eliminamos recursivamente el sucesor duplicado de la rama derecha
            u -> right = erase(u -> right, temp -> data);
        }

        // 3. Al volver de la recursión, rebalanceamos obligatoriamente cada ancestro
        return rebalance(u);
    }

    // Interfaz pública para que el usuario la use desde el main
    void erase(data_type value) {
        root = erase(root, value);
    }

    // SUCESOR: El menor de los elementos mayores que 'val'
    TreeNode* successor(TreeNode* node, data_type val) {
        TreeNode* curr = node;
        TreeNode* succ = nullptr;
        while (curr != nullptr) {
            if (curr->data > val) {
                succ = curr;
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return succ;
    }

    // PREDECESOR: El mayor de los elementos menores que 'val'
    TreeNode* predecessor(TreeNode* node, data_type val) {
        TreeNode* curr = node;
        TreeNode* pred = nullptr;
        while (curr != nullptr) {
            if (curr->data < val) {
                pred = curr;
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        return pred;
    }

    void masCercano(data_type x) {
        TreeNode* exacto = buscar_nodo(root, x);
        if (exacto != nullptr) {
            cout << exacto->data << "\n";
            return;
        }

        TreeNode* pred_node = predecessor(root, x);
        TreeNode* succ_node = successor(root, x);

        long long mejor_estacion = -1;
        long long menor_distancia = -1;

        if (pred_node != nullptr) {
            long long y = pred_node->data;
            long long dist = abs((long long)x - y);
            mejor_estacion = y;
            menor_distancia = dist;
        }

        if (succ_node != nullptr) {
            long long y = succ_node->data;
            long long dist = abs((long long)x - y);

            if (menor_distancia == -1 || dist < menor_distancia) {
                menor_distancia = dist;
                mejor_estacion = y;
            }
            else if (dist == menor_distancia) {
                if (y < mejor_estacion) {
                    mejor_estacion = y;
                }
            }
        }

        cout << mejor_estacion << "\n";
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    if (!(cin >> n)) return 0;
    AVL<int> T;
    for (int i = 0; i < n; i++) {
        int op;
        if (!(cin >> op)) return 0;
        long long dato;
        if (!(cin >> dato)) return 0;
        switch (op) {
            case 1:
                T.insert(dato); break;
            case 2:
                T.erase(dato); break;
            case 3:
                T.masCercano(dato); break;
        }
    }
    return 0;
}