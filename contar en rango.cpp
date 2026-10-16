#include <iostream>
using namespace std;

#include <iostream>

using namespace std;

template<typename data_type>
struct AVL {

    struct TreeNode {
        int height;
        data_type data;
        int count; // Frecuencia para manejar valores repetidos
        TreeNode* left;
        TreeNode* right;

        TreeNode(data_type data = data_type(), int height = 0,
                    TreeNode* left = nullptr,
                    TreeNode* right = nullptr) :
                    data(data), height(height), count(1), left(left), right(right) {}
    };

    TreeNode* root;

    AVL() {
        root = nullptr;
    }

    int h(TreeNode* u) {
        return u == nullptr ? -1 : u -> height;
    }

    // Reemplazamos std::max usando un operador ternario nativo
    void update(TreeNode* u) {
        int hl = h(u -> left);
        int hr = h(u -> right);
        u -> height = 1 + (hl > hr ? hl : hr);
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

    TreeNode* max_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current -> right != nullptr) {
            current = current -> right;
        }
        return current;
    }

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
            u -> count++; // Incrementa frecuencia si se repite
            return u;
        }
        return rebalance(u);
    }

    void insert(data_type value) {
        root = insert(root, value);
    }

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
            temp->count = 1;
            u -> right = erase(u -> right, temp -> data);
        }
        return rebalance(u);
    }

    void erase(data_type value) {
        root = erase(root, value);
    }

    long long contar_rango(TreeNode* u, data_type l, data_type r) {
        if (u == nullptr) return 0;

        long long total = 0;
        if (u->data >= l && u->data <= r) {
            total += u->count;
        }
        if (u->data > l) {
            total += contar_rango(u->left, l, r);
        }
        if (u->data < r) {
            total += contar_rango(u->right, l, r);
        }
        return total;
    }

    long long contar_rango(data_type l, data_type r) {
        return contar_rango(root, l, r);
    }
};

int main() {
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
            T.insert(x);
        }
        else if (op == 2) {
            long long x;
            cin >> x;
            T.erase(x);
        }
        else if (op == 3) {
            long long l, r;
            cin >> l >> r;
            cout << T.contar_rango(l, r) << "\n";
        }
    }
    return 0;
}