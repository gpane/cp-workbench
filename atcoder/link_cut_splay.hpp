//
// Created by Gianluca Pane on 5/16/21.
//

#ifndef CPP_LINK_CUT_SPLAY_HPP
#define CPP_LINK_CUT_SPLAY_HPP

#include <vector>

using namespace std;

struct splay_tree {
    // from https://codeforces.com/blog/entry/75885
    struct Node {
        int ch[2] = {0, 0}, p = 0;
        long long self = 0, path = 0;        // Path aggregates
        long long sub = 0, vir = 0;          // Subtree aggregates
        bool flip = 0;                       // Lazy tags
    };
    vector<Node> T;

    splay_tree(int n) : T(n + 1) {}

    void push(int x) {
        if (!x || !T[x].flip) return;
        int l = T[x].ch[0], r = T[x].ch[1];

        T[l].flip ^= 1, T[r].flip ^= 1;
        swap(T[x].ch[0], T[x].ch[1]);
        T[x].flip = 0;
    }

    void pull(int x) {
        int l = T[x].ch[0], r = T[x].ch[1]; push(l); push(r);

        T[x].path = T[l].path + T[x].self + T[r].path;
        T[x].sub = T[x].vir + T[l].sub + T[r].sub + T[x].self;
    }

    void set(int x, int d, int y) {
        T[x].ch[d] = y; T[y].p = x; pull(x);
    }

    void splay(int x) {
        auto dir = [&](int x) {
            int p = T[x].p; if (!p) return -1;
            return T[p].ch[0] == x ? 0 : T[p].ch[1] == x ? 1 : -1;
        };
        auto rotate = [&](int x) {
            int y = T[x].p, z = T[y].p, dx = dir(x), dy = dir(y);
            set(y, dx, T[x].ch[!dx]);
            set(x, !dx, y);
            if (~dy) set(z, dy, x);
            T[x].p = z;
        };
        for (push(x); ~dir(x); ) {
            int y = T[x].p, z = T[y].p;
            push(z); push(y); push(x);
            int dx = dir(x), dy = dir(y);
            if (~dy) rotate(dx != dy ? x : y);
            rotate(x);
        }
    }
};


class link_cut_tree : splay_tree {
    // from https://codeforces.com/blog/entry/75885
public:
    link_cut_tree(int n) : splay_tree(n) {}

    void link(int u, int v) {
        reroot(u); access(v);
        T[v].vir += T[u].sub;
        T[u].p = v; pull(v);
    }

    void cut(int u, int v) {
        reroot(u); access(v);
        T[v].ch[0] = T[u].p = 0; pull(v);
    }

    // Rooted tree LCA. Returns 0 if u and v arent connected.
    int lca(int u, int v) {
        if (u == v) return u;
        access(u); int ret = access(v);
        return T[u].p ? ret : 0;
    }

    // Query subtree of u where v is outside the subtree.
    long long subtree(int u, int v) {
        reroot(v); access(u); return T[u].vir + T[u].self;
    }

    // Query path [u..v]
    long long path(int u, int v) {
        reroot(u); access(v); return T[v].path;
    }

    // Update vertex u with value v
    void update(int u, long long v) {
        access(u); T[u].self = v; pull(u);
    }

private:
    int access(int x) {
        int u = x, v = 0;
        for (; u; v = u, u = T[u].p) {
            splay(u);
            int& ov = T[u].ch[1];
            T[u].vir += T[ov].sub;
            T[u].vir -= T[v].sub;
            ov = v; pull(u);
        }
        return splay(x), v;
    }

    void reroot(int x) {
        access(x); T[x].flip ^= 1; push(x);
    }
};


#endif // CPP_LINK_CUT_SPLAY_HPP
