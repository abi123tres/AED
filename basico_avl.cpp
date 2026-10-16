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
    TreeNode* buscar_nodo(TreeNode* u, data_type key) {
        if (u == nullptr || u->data == key) {
            return u; // Si lo encuentra o llega a nulo, retorna el nodo (o nullptr)
        }
        if (key < u->data) {
            return buscar_nodo(u->left, key); // Busca por la izquierda
        }
        return buscar_nodo(u->right, key);     // Busca por la derecha
    }

    /*
    // 1. Buscamos el nodo que contiene el valor 40
TreeNode* nodo_encontrado = T.buscar_nodo(T.root, 40);

// 2. Verificamos si existe y obtenemos su altura con seguridad
if (nodo_encontrado != nullptr) {
    cout << "La altura es: " << T.h(nodo_encontrado) << "\n";
} else {
    cout << "El valor no existe en el árbol.\n";
}
     */


    TreeNode* erase_using_successor(TreeNode* u, data_type key) {
        if (u == nullptr) return nullptr;

        if (key < u -> data) {
            u -> left = erase_using_successor(u -> left, key);
        }
        else if (key > u -> data) {
            u -> right = erase_using_successor(u -> right, key);
        }
        else {
            // Caso 1: Cero hijos o un solo hijo (el derecho o izquierdo sube)
            if (u -> left == nullptr) {
                TreeNode* temp = u -> right;
                delete u;
                return temp;
            }
            else if (u -> right == nullptr) {
                TreeNode* temp = u -> left;
                delete u;
                return temp;
            }

            // Caso 2: Dos hijos -> Usamos el MÍNIMO del subárbol DERECHO (Sucesor)
            TreeNode* temp = min_element(u -> right);
            u -> data = temp -> data; // Reemplazamos la clave
            u -> right = erase_using_successor(u -> right, temp -> data); // Borramos el duplicado
        }

        return rebalance(u); // Rebalanceo obligatorio al volver
    }

    TreeNode* erase_using_predecessor(TreeNode* u, data_type key) {
        if (u == nullptr) return nullptr;

        if (key < u -> data) {
            u -> left = erase_using_predecessor(u -> left, key);
        }
        else if (key > u -> data) {
            u -> right = erase_using_predecessor(u -> right, key);
        }
        else {
            // Caso 1: Cero hijos o un solo hijo (igual que antes)
            if (u -> left == nullptr) {
                TreeNode* temp = u -> right;
                delete u;
                return temp;
            }
            else if (u -> right == nullptr) {
                TreeNode* temp = u -> left;
                delete u;
                return temp;
            }

            // Caso 2: Dos hijos -> Usamos el MÁXIMO del subárbol IZQUIERDO (Predecesor)
            TreeNode* temp = max_element(u -> left);
            u -> data = temp -> data; // Reemplazamos la clave
            u -> left = erase_using_predecessor(u -> left, temp -> data); // Borramos el duplicado a la izquierda
        }

        return rebalance(u); // Rebalanceo obligatorio al volver
    }

    // Función recursiva privada para eliminar una clave
    TreeNode* erase(TreeNode* u, data_type key) {
        // 1. Caso base: si llegamos a un nodo nulo, la clave no está en el árbol
        if (u == nullptr) return nullptr;

        // 2. Descenso recursivo buscando la clave
        if (key < u -> data) {
            u -> left = erase(u -> left, key);
        }
        else if (key > u -> data) {
            u -> right = erase(u -> right, key);
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
    // Retorna el nodo con la clave mínima a partir de un nodo 'u'
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

    // Encuentra el nodo que contiene exactamente una clave 'key'
    TreeNode* find_node(TreeNode* u, data_type key) {
        if (u == nullptr || u->data == key) {
            return u;
        }
        if (key < u->data) {
            return find_node(u->left, key);
        }
        return find_node(u->right, key);
    }

    // SUCESOR: El menor de los mayores (el siguiente elemento en orden in-order)
    TreeNode* successor(TreeNode* root_node, data_type key) {
        TreeNode* current = find_node(root_node, key);
        if (current == nullptr) return nullptr;

        // Caso 1: Si tiene subárbol derecho, el sucesor es el mínimo de ese subárbol
        if (current->right != nullptr) {
            return min_element(current->right);
        }

        // Caso 2: Si no tiene subárbol derecho, subimos por los ancestros
        // buscando el último ancestro del cual fuimos hijo izquierdo.
        TreeNode* succ = nullptr;
        TreeNode* ancestor = root_node;
        while (ancestor != current) {
            if (current->data < ancestor->data) {
                succ = ancestor; // Este ancestro es un candidato mayor
                ancestor = ancestor->left;
            } else {
                ancestor = ancestor->right;
            }
        }
        return succ;
    }

    // PREDECESOR: El mayor de los menores (el elemento anterior en orden in-order)
    TreeNode* predecessor(TreeNode* root_node, data_type key) {
        TreeNode* current = find_node(root_node, key);
        if (current == nullptr) return nullptr;

        // Caso 1: Si tiene subárbol izquierdo, el predecesor es el máximo de ese subárbol
        if (current->left != nullptr) {
            return max_element(current->left);
        }

        // Caso 2: Si no tiene subárbol izquierdo, subimos por los ancestros
        // buscando el último ancestro del cual fuimos hijo derecho.
        TreeNode* pred = nullptr;
        TreeNode* ancestor = root_node;
        while (ancestor != current) {
            if (current->data > ancestor->data) {
                pred = ancestor; // Este ancestro es un candidato menor
                ancestor = ancestor->right;
            } else {
                ancestor = ancestor->left;
            }
        }
        return pred;
    }
};