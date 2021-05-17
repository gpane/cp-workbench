#include <iostream>
#include <fstream>

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
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
#include "testlib/testlib.h"

#define ll long long
using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); i++)

// t measures "elongation"
// For n = 10, t = 100, a path graph (degree of all vertices are at most 2) is likely to be generated.
// For n = 10, t = -1000, a star graph (there's only one non-leaf vertex in the tree) is likely to be generated.
void make_tree(int n, int t) {
    vector<int> p(n);
    forn(i, n)
        if (i > 0)
            p[i] = rnd.wnext(i, t);

//    printf("%d\n", n);  // uncomment to print n
    vector<int> perm(n);
    forn(i, n)
        perm[i] = i;
    shuffle(perm.begin() + 1, perm.end());
    vector<pair<int,int> > edges;

    for (int i = 1; i < n; i++)
        if (rnd.next(2))
            edges.emplace_back(perm[i], perm[p[i]]);
        else
            edges.emplace_back(perm[p[i]], perm[i]);

    shuffle(edges.begin(), edges.end());

    for (int i = 0; i + 1 < n; i++)
        printf("%d %d\n", edges[i].first + 1, edges[i].second + 1);
}

int main(int argc, char *argv[]) {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
}

