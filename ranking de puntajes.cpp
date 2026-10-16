#include <iostream>

using namespace std;

template<typename data_type>
struct AVL {

    struct TreeNode {
        int height;
        data_type data;
        long long sub_size; // Cantidad de elementos en este subárbol
        TreeNode* left;
        TreeNode* right;

        TreeNode(data_type data = data_type(), int height = 0,
                    TreeNode* left = nullptr,
                    TreeNode* right = nullptr) :
                    data(data), height(height), sub_size(1), left(left), right(right) {}
    };

    TreeNode* root;

    AVL() {
        root = nullptr;
    }

    int h(TreeNode* u) {
        return u == nullptr ? -1 : u -> height;
    }

    long long sz(TreeNode* u) {
        return u == nullptr ? 0 : u -> sub_size;
    }

    // Actualizamos altura y sub_size en O(1)
    void update(TreeNode* u) {
        int hl = h(u -> left);
        int hr = h(u -> right);
        u -> height = 1 + (hl > hr ? hl : hr);
        u -> sub_size = 1 + sz(u -> left) + sz(u -> right);
    }

    int FB(TreeNode* u) {
        return h(u -> left) - h(u -> right);
    }

    TreeNode* rotate_left(TreeNode* u) {
        TreeNode* v = u -> right;
        u -> right = v -> left;
        v -> left = u;
        update(u);
        update(v);
        return v;
    }

    TreeNode* rotate_right(TreeNode* u) {
        TreeNode* v = u -> left;
        u -> left = v -> right;
        v -> right = u;
        update(u);
        update(v);
        return v;
    }

    TreeNode* rebalance(TreeNode* u) {
        update(u);
        if (FB(u) > 1) {
            if (FB(u -> left) < 0) {
                u -> left = rotate_left(u -> left);
            }
            return rotate_right(u);
        }
        if (FB(u) < -1) {
            if (FB(u -> right) > 0) {
                u -> right = rotate_right(u -> right);
            }
            return rotate_left(u);
        }
        return u;
    }

    // Inserción de un nuevo puntaje (se garantiza que no está repetido)
    TreeNode* insert(TreeNode* u, data_type value) {
        if (u == nullptr) {
            return new TreeNode(value, 0);
        }
        if (value < u -> data) {
            u -> left = insert(u -> left, value);
        }
        else if (value > u -> data) {
            u -> right = insert(u -> right, value);
        }
        return rebalance(u);
    }

    void insert(data_type value) {
        root = insert(root, value);
    }

    // Cuenta cuántos puntajes almacenados son estrictamente menores que 'limit' en O(log n)
    long long count_strictly_less(TreeNode* u, data_type limit) {
        if (u == nullptr) return 0;

        if (u -> data >= limit) {
            // Si el nodo actual es mayor o igual, buscamos únicamente en la izquierda
            return count_strictly_less(u -> left, limit);
        } else {
            // Si el nodo actual es menor, sumamos 1 (el nodo), todo el subárbol izquierdo, y exploramos la derecha
            return 1 + sz(u -> left) + count_strictly_less(u -> right, limit);
        }
    }

    long long count_strictly_less(data_type limit) {
        return count_strictly_less(root, limit);
    }
};

int main() {
    // Optimización de E/S para competencia
    cin.tie(0) -> sync_with_stdio(false);

    int q;
    if (!(cin >> q)) return 0;

    AVL<long long> T;

    for (int i = 0; i < q; i++) {
        int t;
        long long x;
        if (!(cin >> t >> x)) return 0;

        if (t == 1) {
            T.insert(x); // Registrar el puntaje
        }
        else if (t == 2) {
            // Responder cuántos puntajes son estrictamente menores que x
            cout << T.count_strictly_less(x) << "\n";
        }
    }

    return 0;
}