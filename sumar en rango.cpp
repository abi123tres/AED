#include <iostream>

using namespace std;

template<typename data_type>
struct AVL {

    struct TreeNode {
        int height;
        data_type data;       // Precio del producto
        long long count;      // Cuántos productos tienen este precio exacto
        long long sub_sum;    // Suma total de los precios en este subárbol
        TreeNode* left;
        TreeNode* right;

        TreeNode(data_type data = data_type(), int height = 0,
                    TreeNode* left = nullptr,
                    TreeNode* right = nullptr) :
                    data(data), height(height), count(1), sub_sum(data), left(left), right(right) {}
    };

    TreeNode* root;

    AVL() {
        root = nullptr;
    }

    int h(TreeNode* u) {
        return u == nullptr ? -1 : u -> height;
    }

    long long get_sum(TreeNode* u) {
        return u == nullptr ? 0 : u -> sub_sum;
    }

    // Actualizamos la altura y la suma total del subárbol en O(1)
    void update(TreeNode* u) {
        int hl = h(u -> left);
        int hr = h(u -> right);
        u -> height = 1 + (hl > hr ? hl : hr);
        u -> sub_sum = (u -> data * u -> count) + get_sum(u -> left) + get_sum(u -> right);
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

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current -> left != nullptr) {
            current = current -> left;
        }
        return current;
    }

    // Inserción con manejo de frecuencias (precios repetidos)
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
        else {
            u -> count++; // Incrementa la frecuencia si el precio ya existe
            update(u);
            return u;
        }
        return rebalance(u);
    }

    void insert(data_type value) {
        root = insert(root, value);
    }

    // Eliminación con manejo de frecuencias (se vende un producto de precio x)
    TreeNode* erase(TreeNode* u, data_type val) {
        if (u == nullptr) return nullptr;

        if (val < u -> data) {
            u -> left = erase(u -> left, val);
        }
        else if (val > u -> data) {
            u -> right = erase(u -> right, val);
        }
        else {
            if (u -> count > 1) {
                u -> count--;
                update(u);
                return u;
            }

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

            TreeNode* temp = min_element(u -> right);
            u -> data = temp -> data;
            u -> count = temp -> count;
            temp -> count = 1; // Para facilitar el borrado físico del sucesor
            u -> right = erase(u -> right, temp -> data);
        }
        return rebalance(u);
    }

    void erase(data_type value) {
        root = erase(root, value);
    }

    // Suma de precios menores o iguales a 'limit' en O(log n)
    long long sum_le(TreeNode* u, data_type limit) {
        if (u == nullptr) return 0;
        if (u -> data <= limit) {
            return get_sum(u -> left) + (u -> data * u -> count) + sum_le(u -> right, limit);
        } else {
            return sum_le(u -> left, limit);
        }
    }

    // Suma de precios en el rango [l, r] usando la resta de acumulados
    long long sum_range(data_type l, data_type r) {
        return sum_le(root, r) - sum_le(root, l - 1);
    }
};

int main() {
    // Optimización de E/S para competencia
    cin.tie(0) -> sync_with_stdio(false);

    int q;
    if (!(cin >> q)) return 0;

    AVL<long long> T;

    for (int i = 0; i < q; i++) {
        int op;
        if (!(cin >> op)) return 0;

        if (op == 1) {
            long long x;
            cin >> x;
            T.insert(x); // Llega un producto de precio x
        }
        else if (op == 2) {
            long long x;
            cin >> x;
            T.erase(x);  // Se vende un producto de precio x
        }
        else if (op == 3) {
            long long l, r;
            cin >> l >> r;
            // Responder la suma de precios entre l y r, inclusive
            cout << T.sum_range(l, r) << "\n";
        }
    }

    return 0;
}