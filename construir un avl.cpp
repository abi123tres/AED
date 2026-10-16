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

};

int main (){
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    if (!(cin >> n)) return 0;
    AVL<int> T;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        T.insert(x);
        cout << T.h(T.root) << " " << T.root -> data << endl;
    }
    return 0;
}