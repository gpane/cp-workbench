//
// Created by Gianluca Pane on 5/15/21.
//

#ifndef CPP_SPARSE_TABLE_HPP
#define CPP_SPARSE_TABLE_HPP

#include <vector>

using namespace std;

// Sparse table that gives indices as well as values.
// Works on functions where f(x, y) = x or f(x, y) = y.
// Would need to use a different sparse table implementation for gcd, for example.
template<class T, T (*op)(T, T)>
class sparse_table {
private:
    vector<T> arr;
    vector<vector<int>> table;

public:
    sparse_table(vector<T> arr) : arr(arr) {
        table.resize(arr.size(), vector<int>(32 - __builtin_clz((int) arr.size()), -1));
        for (int i = 0; i < (int) arr.size(); i++) table[i][0] = i;

        for (int j = 1; j < (int) table[0].size(); j++) {
            // [i, i + 2^j - 1] = [i, i + 2^(j-1) - 1] + [i + 2^(j-1), i + 2^j - 1]
            for (int i = 0; i + (1 << j) - 1 < (int) arr.size(); i++) {
                assert(table[i + (1 << (j - 1))][j - 1] != -1);
                T res = op(arr[table[i][j - 1]], arr[table[i + (1 << (j - 1))][j - 1]]);
                if (res == arr[table[i][j - 1]]) table[i][j] = table[i][j - 1];
                else {
                    assert(res == arr[table[i + (1 << (j - 1))][j - 1]]);
                    table[i][j] = table[i + (1 << (j - 1))][j - 1];
                }
            }
        }
    }

    int queryFirstIndex(int l, int r) {
        assert(l >= 0 && r < (int) arr.size() && l <= r);
        int best = -1;
        int curr = l;
        auto compare = [&](int candidate) {
            if (best == -1 || op(arr[best], arr[candidate]) != arr[best]) {
                best = candidate;
            }
        };
        while (curr <= r) {
            for (int j = (int) table[0].size() - 1; j >= 0; j--) {
                if (curr + (1 << j) - 1 <= r) {
                    compare(table[curr][j]);
                    curr += 1 << j;
                }
            }
        }
        return best;
    }

    T query(int l, int r) {
        return arr[queryFirstIndex(l, r)];
    }
};


#endif //CPP_SPARSE_TABLE_HPP
