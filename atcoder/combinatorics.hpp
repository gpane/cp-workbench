#ifndef CPP_COMBINATORICS_HPP
#define CPP_COMBINATORICS_HPP

#include <vector>
#include <atcoder/modint.hpp>

using namespace std;
using namespace atcoder;

template<class T>
struct combinatorics {
    combinatorics(int n) {
        MAXN = n;
        factorials = vector<T>(MAXN + 1, T(1));
        inv_factorials = vector<T>(MAXN + 1, T(1).inv());
        T curr = factorials[0];
        T curr_inv = inv_factorials[0];
        for (int i = 1; i <= MAXN; i++) {
            curr *= i;
            factorials[i] = curr;
            curr_inv *= T(i).inv();
            inv_factorials[i] = curr_inv;
        }
    }

    T fact(int n) {
        return factorials[n];
    }

    T binom(int n, int k) {
        return factorials[n] * inv_factorials[k] * inv_factorials[n - k];
    }

    // ways to partition sum(sizes) elements into sets of the provided sizes
    T ways_to_partition(vector<int> sizes) {
        int elts = accumulate(sizes.begin(), sizes.end(), 0);
        T ans = T(1);
        for (int size : sizes) {
            ans *= binom(elts, size);
            elts -= size;
        }
        return ans;
    }

private:
    int MAXN;
    vector<T> factorials;
    vector<T> inv_factorials;
};

#endif //CPP_COMBINATORICS_HPP
