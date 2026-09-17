#include <iostream>

using namespace std;


void swap_val(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}


void quicksort(int* arr, int izq, int der) {
    if (izq >= der) return;

    int pivote = arr[izq + (der - izq) / 2];
    int i = izq;
    int j = der;

    while (i <= j) {
        while (arr[i] < pivote) i++;
        while (arr[j] > pivote) j--;
        if (i <= j) {
            swap_val(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (izq < j) quicksort(arr, izq, j);
    if (i < der) quicksort(arr, i, der);
}


int primer_indice(const int* arr, int n, int x) {
    int low = 0, high = n - 1;
    int ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            ans = mid;
            high = mid - 1;
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}


int ultimo_indice(const int* arr, int n, int x) {
    int low = 0, high = n - 1;
    int ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            ans = mid;
            low = mid + 1;
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    int* a = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    quicksort(a, 0, n - 1);

    for (int i = 0; i < q; ++i) {
        int x;
        cin >> x;

        int primero = primer_indice(a, n, x);
        if (primero == -1) {
            cout << 0 << "\n";
        } else {
            int ultimo = ultimo_indice(a, n, x);
            cout << (ultimo - primero + 1) << "\n";
        }
    }

    delete[] a;
    return 0;
}