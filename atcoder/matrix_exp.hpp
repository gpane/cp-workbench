#ifndef CPP_MATRIX_EXP_HPP
#define CPP_MATRIX_EXP_HPP

#include <vector>

using namespace std;

template <class T>
void matrix_mult(vector<vector<T>>& a, vector<vector<T>>& b, vector<vector<T>>& into) {
    int n = size(a);
    int m = size(a[0]);
    assert(m == size(b));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                into[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

template <class T>
vector<vector<T>> matrix_exp(vector<vector<T>>& m, T exp) {
    vector<vector<T>> out = vector<vector<T>>(size(m), vector<T>(size(m[0])));
    for (int i = 0; i < min(size(m), size(m[0])); i++) {
        out[i][i] = 1;
    }
    vector<vector<T>> storage = vector<vector<T>>(size(m), vector<T>(size(m[0])));
    while (exp > 0) {
        if (exp % 2 == 1) {
            matrix_mult(out, m, storage);
            swap(storage, out);
        }
        matrix_mult(m, m, storage);
        swap(storage, m);

        exp >>= 1;
    }
    return out;
}

#endif //CPP_MATRIX_EXP_HPP
