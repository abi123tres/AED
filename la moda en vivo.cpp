#include <iostream>

using namespace std;

template<typename data_type>
struct AVL {

    struct TreeNode {
        int height;
        data_type song_id; // ID de la canción
        long long votes;   // Cantidad de votos que tiene
        TreeNode* left;
        TreeNode* right;

        TreeNode(data_type song_id, long long votes = 1, int height = 0,
                    TreeNode* left = nullptr, TreeNode* right = nullptr) :
                    song_id(song_id), votes(votes), height(height), left(left), right(right) {}
    };

    TreeNode* root;

    // Variables para mantener la moda actual y evitar buscarla desde cero
    long long max_votes;
    data_type best_song;

    AVL() {
        root = nullptr;
        max_votes = -1;
        best_song = -1;
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

    // Función para evaluar si este nodo se convierte en la nueva moda
    void check_moda(data_type id, long long v) {
        if (v > max_votes) {
            max_votes = v;
            best_song = id;
        } else if (v == max_votes) {
            if (id < best_song) {
                best_song = id;
            }
        }
    }

    // Inserción o incremento de votos de una canción
    TreeNode* insert(TreeNode* u, data_type song_id) {
        if (u == nullptr) {
            TreeNode* nuevo = new TreeNode(song_id, 1, 0);
            check_moda(song_id, 1);
            return nuevo;
        }
        if (song_id < u -> song_id) {
            u -> left = insert(u -> left, song_id);
        }
        else if (song_id > u -> song_id) {
            u -> right = insert(u -> right, song_id);
        }
        else {
            u -> votes++; // Aumenta los votos de la canción existente
            check_moda(u -> song_id, u -> votes);
            return u;
        }
        return rebalance(u);
    }

    void insert(data_type song_id) {
        root = insert(root, song_id);
    }

    // Búsqueda auxiliar para recalcular la moda si la moda actual pierde votos
    void encontrar_moda_global(TreeNode* u) {
        if (u == nullptr) return;
        check_moda(u->song_id, u->votes);
        encontrar_moda_global(u->left);
        encontrar_moda_global(u->right);
    }

    // Eliminación o decremento de votos de una canción
    TreeNode* erase(TreeNode* u, data_type song_id) {
        if (u == nullptr) return nullptr;

        if (song_id < u -> song_id) {
            u -> left = erase(u -> left, song_id);
        }
        else if (song_id > u -> song_id) {
            u -> right = erase(u -> right, song_id);
        }
        else {
            // Si tiene más de 1 voto, solo restamos uno
            if (u -> votes > 1) {
                u -> votes--;
                // Si la canción eliminada era la moda y bajaron sus votos, debemos recalcular
                if (song_id == best_song) {
                    max_votes = -1;
                    best_song = -1;
                    encontrar_moda_global(root);
                }
                return u;
            }

            // Si llega a 0 votos, se elimina el nodo del árbol
            if (u -> left == nullptr) {
                TreeNode* temp = u -> right;
                if (song_id == best_song) {
                    max_votes = -1;
                    best_song = -1;
                    encontrar_moda_global(root);
                }
                delete u;
                return temp;
            }
            else if (u -> right == nullptr) {
                TreeNode* temp = u -> left;
                if (song_id == best_song) {
                    max_votes = -1;
                    best_song = -1;
                    encontrar_moda_global(root);
                }
                delete u;
                return temp;
            }

            TreeNode* temp = min_element(u -> right);
            u -> song_id = temp -> song_id;
            u -> votes = temp -> votes;
            temp -> votes = 1; // Para facilitar el borrado físico del sucesor
            u -> right = erase(u -> right, temp -> song_id);

            if (song_id == best_song) {
                max_votes = -1;
                best_song = -1;
                encontrar_moda_global(root);
            }
        }
        return rebalance(u);
    }

    void erase(data_type song_id) {
        root = erase(root, song_id);
    }

    void imprimir_moda() {
        cout << best_song << " " << max_votes << "\n";
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
            T.imprimir_moda();
        }
    }
    return 0;
}