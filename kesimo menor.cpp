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

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current -> left != nullptr) {
            current = current -> left;
        }
        return current;
    }

    // Inserción de un nuevo código de libro único
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

    // Eliminación de un código de libro disponible
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

    // Encuentra el k-ésimo elemento más pequeño en O(log n)
    data_type find_kth(TreeNode* u, long long k) {
        if (u == nullptr) return -1;
        long long left_size = sz(u -> left);

        if (k == left_size + 1) {
            return u -> data;
        }
        else if (k <= left_size) {
            return find_kth(u -> left, k);
        }
        else {
            return find_kth(u -> right, k - left_size - 1);
        }
    }

    data_type find_kth(long long k) {
        return find_kth(root, k);
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
        long long y;
        if (!(cin >> t >> y)) return 0;

        if (t == 1) {
            T.insert(y); // Llega un libro nuevo
        }
        else if (t == 2) {
            T.erase(y);  // Sale prestado un libro
        }
        else if (t == 3) {
            // Responder el k-ésimo menor código disponible
            cout << T.find_kth(y) << "\n";
        }
    }

    return 0;
}