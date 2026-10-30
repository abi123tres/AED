#include <iostream>
#include <vector>
#include <string>
using namespace std;

void construirCodigos (int longitud, string actCod, vector<string>& codigos) {
    if (actCod.length() == longitud) {
        codigos.push_back(actCod);
        return;
    }
    construirCodigos (longitud, actCod + '0', codigos);
    if (actCod.empty() | actCod.back() != '1') {
        construirCodigos (longitud, actCod + '1', codigos);
    }
}


int main () {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    if (!(cin >> n)) return 0;
    vector<string> res;
    construirCodigos(n, "", res);
    cout << res.size() << "\n";
    for (string s : res) {
        cout << s << "\n";
    }
    return 0;
}















