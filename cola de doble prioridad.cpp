#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int height;
    int data;
    int count;
    int left;
    int right;

    Node (int val) : data(val), count(-1), height(0), left(-1), right(-1) {}
    };
vector<Node> tree;
int root = -1;

int h(int u) {
    return u == -1 ? -1 : tree[u].height;
}

void update(int u) {
    tree[u].height = 1 + max(h(tree[u].left), h(tree[u].right));
}

int FB(int u) {
    return h(tree[u].left) - h(tree[u].right);
}

int rotate_left(int u) {
    int v = tree[u].right;
    tree[u].right = tree[v].left;
    tree[v].left = u;
    update(u);
    update(v);
    return v;
}

int rotate_right(int u) {
    int v = tree[u].left;
    tree[u].left = tree[v].right;
    tree[v].right = u;
    update(u);
    update(v);
    return v;
}

int rebalance(int u) {
    update(u);
    if (FB(u) > 1) {
        if (FB(tree[u].left) < 0) {
            tree[u].left = rotate_left(tree[u].left);
        }
        return rotate_right(u);
    }
    if (FB(u) < -1) {
        if (FB(tree[u].right) > 0) {
            tree[u].right = rotate_right(tree[u].right);
        }
        return rotate_left(u);
    }
    return u;
}

int insert(int u, int value) {
    if (u == -1) {
        tree.push_back(Node(value));
        return tree.size() - 1;
    }

    if (value < tree[u].data) {
        tree[u].left = insert(tree[u].left, value);
    } else if (value > tree[u].data) {
        tree[u].right = insert(tree[u].right, value);
    } else {
        tree[u].count++;
        return u;
    }

    return rebalance(u);
}

int min_element(int u) {
    if (u == -1) return -1;
    while (tree[u].left != -1) {
        u = tree[u].left;
    }
    return u;
}

int max_element(int u) {
    if (u == -1) return -1;
    while (tree[u].right != -1) {
        u = tree[u].right;
    }
    return u;
}

int erase(int u, int key) {
    if (u == -1) return -1;

    if (key < tree[u].data) {
        tree[u].left = erase(tree[u].left, key);
    } else if (key > tree[u].data) {
        tree[u].right = erase(tree[u].right, key);
    } else {
        if (tree[u].count > 1) {
            tree[u].count--;
            return u;
        }

        if (tree[u].left == -1) return tree[u].right;
        if (tree[u].right == -1) return tree[u].left;

        int temp = min_element(tree[u].right);
        tree[u].data = tree[temp].data;
        tree[u].count = tree[temp].count;
        tree[temp].count = 1;
        tree[u].right = erase(tree[u].right, tree[temp].data);
    }

    return rebalance(u);
}

int popMin () {
    int indice = min_element(root);
    int val = tree[indice].data;
    root = erase(root, val);
    return val;
}

int popMax () {
    int indice = max_element(root);
    int val = tree[indice].data;
    root = erase(root, val);
    return val;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    long long n;
    if (!(cin >> n)) return 0;
    while (n--) {
        int op;
        cin >> op;

        if (op == 1) {
            int x;
            cin >> x;
            root = insert(root, x);
        } else if (op == 2) {
            if (root == -1) {
                cout << "VACIA\n";
            } else {
                cout << popMin() << "\n";
            }
        } else if (op == 3) {
            if (root == -1) {
                cout << "VACIA\n";
            } else {
                cout << popMax() << "\n";
            }
        }
    }
    return 0;
}
























/*
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> q)) return 0;

    while (q--) {
        int tipo;
        cin >> tipo;

        if (tipo == 1) {
            int x;
            cin >> x;
            root = insert(root, x);
        } else if (tipo == 2) {
            if (root == -1) {
                cout << "VACIA\n";
            } else {
                cout << pop_min() << "\n";
            }
        } else if (tipo == 3) {
            if (root == -1) {
                cout << "VACIA\n";
            } else {
                cout << pop_max() << "\n";
            }
        }
    }

    return 0;
}*/