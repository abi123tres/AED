#include <iostream>
using namespace std;

struct Interval {
    long long s, e;

    bool operator<(const Interval& other) const {
        return s < other.s;
    }
    bool operator>(const Interval& other) const {
        return s > other.s;
    }
    bool operator==(const Interval& other) const {
        return s == other.s;
    }
    bool operator!=(const Interval& other) const {
        return s != other.s;
    }
};

template<typename data_type>
struct AVL {

    struct TreeNode {
        int height;
        data_type data;
        TreeNode* left;
        TreeNode* right;

        TreeNode(data_type data = data_type(), int height = 0,
                    TreeNode* left = nullptr,
                    TreeNode* right = nullptr) :
                    data(data), height(height), left(left), right(right) {}
    };

    TreeNode* root;

    AVL() {
        root = nullptr;
    }

    int h(TreeNode* u) {
        return u == nullptr ? -1 : u -> height;
    }

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
            return u;
        }
        return rebalance(u);
    }

    void insert(data_type value) {
        root = insert(root, value);
    }

    TreeNode* buscar_nodo(TreeNode* u, data_type val) {
        if (u == nullptr || u->data == val) {
            return u;
        }
        if (val < u->data) {
            return buscar_nodo(u->left, val);
        }
        return buscar_nodo(u->right, val);
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
            u -> right = erase(u -> right, temp -> data);
        }
        return rebalance(u);
    }

    void erase(data_type value) {
        root = erase(root, value);
    }

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
}; // <--- Esta llave cierra struct AVL correctamente

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int q;
    if (!(cin >> q)) return 0;

    AVL<Interval> T;

    for (int i = 0; i < q; i++) {
        int op;
        if (!(cin >> op)) return 0;

        if (op == 1) {
            long long s, e;
            cin >> s >> e;
            Interval nuevo = {s, e};

            bool choca = false;
            if (T.buscar_nodo(T.root, nuevo) != nullptr) {
                choca = true;
            }

            auto pred = T.predecessor(T.root, nuevo); // Nota: si usas TreeNode* en el main, asegúrate de llamarlo T::TreeNode* o dejarlo encapsulado
            if (pred != nullptr && pred->data.e > s) {
                choca = true;
            }

            auto succ = T.successor(T.root, nuevo);
            if (succ != nullptr && succ->data.s < e) {
                choca = true;
            }

            if (choca) {
                cout << "NO\n";
            } else {
                T.insert(nuevo);
                cout << "SI\n";
            }
        }
        else if (op == 2) {
            long long s;
            cin >> s;
            T.erase({s, 0});
        }
        else if (op == 3) {
            long long t;
            cin >> t;
            auto pred = T.predecessor(T.root, {t + 1, 0});
            if (pred != nullptr && pred->data.e > t) {
                cout << pred->data.s << " " << pred->data.e << "\n";
            } else {
                cout << "LIBRE\n";
            }
        }
    }
    return 0;
}