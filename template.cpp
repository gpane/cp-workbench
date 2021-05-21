#include <iostream>
#include <fstream>

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#define ll long long

namespace atcoder {}

using namespace std;
using namespace atcoder;

template<class T>
void debug(vector<T>& arr) {
    for (int val : arr) cerr << val << ' ';
    cerr << '\n';
}

static bool MULTIPLE_CASES = false;
static long long MOD = (long long) 1e9 + 7;

void solve() {
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (MULTIPLE_CASES) {
        int tests;
        cin >> tests;
        for (int i = 1; i <= tests; i++) {
//            cout << "Case #" << i << ": ";
            solve();
        }
    } else {
        solve();
    }
}
