#ifndef CPP_TREE_HPP
#define CPP_TREE_HPP

#include <atcoder/y_combinator.hpp>
#include <atcoder/sparse_table.hpp>

#include <deque>
#include <iostream>

class tree {
public:
    const int n;
    const vector<vector<int>> adj;

    explicit tree(const vector<vector<int>> &adj) : n(adj.size()), adj(adj) {}
    tree(int n, const vector<pair<int, int>>& edge_list) : n(n), adj(get_adj(n, edge_list)) {}
    tree(int n, bool one_indexed) : n(n), adj(get_adj(n, one_indexed)) {}
    explicit tree(int n) : tree(n, true) {}

    [[nodiscard]] int size() const {
        return n;
    }

    vector<int> get_depths(int root) {
        vector<int> depths(n);
        auto dfs = y_combinator([&](auto self, int v, int par, int depth) -> void {
            depths[v] = depth;
            for (int child : adj[v]) {
                if (child == par) continue;
                self(child, v, depth + 1);
            }
        });
        dfs(root, -1, 0);
        return depths;
    }

    vector<int> get_sizes(int root) {
        vector<int> sizes(n);
        auto dfs = y_combinator([&](auto self, int v, int par) -> int {
            int size = 1;
            for (int child : adj[v]) {
                if (child == par) continue;
                size += self(child, v);
            }
            return sizes[v] = size;
        });
        dfs(root, -1);
        return sizes;
    }

    // for each node, the incoming and outgoing Euler numbers
    vector<pair<int, int>> get_euler_tour(int root) {
        vector<pair<int, int>> euler_tour(n);
        auto dfs = y_combinator([&](auto self, int v, int par, int num) -> int {
            int curr = num;
            euler_tour[v].first = curr;
            for (int child : adj[v]) {
                if (child == par) continue;
                curr++;
                curr = self(child, v, curr);
            }
            euler_tour[v].second = curr;
            return curr;
        });
        assert(dfs(root, -1, 0) == n - 1);
        return euler_tour;
    }

    // vector<vector<int>> for each node, the list of Euler numbers
    // vector<int> (size 2n - 1) for each Euler number, the corresponding node
    pair<vector<vector<int>>, vector<int>> get_euler_tour_path_queries(int root) {
        vector<vector<int>> euler_tour_path_queries(n, vector<int>());
        vector<int> euler_tour_path_queries_rev(2*n - 1);
        auto dfs = y_combinator([&](auto self, int v, int par, int num) -> int {
            int curr = num;
            euler_tour_path_queries[v].push_back(curr);
            for (int child : adj[v]) {
                if (child == par) continue;
                curr++;
                curr = self(child, v, curr);
                curr++;
                euler_tour_path_queries[v].push_back(curr);
            }
            return curr;
        });
        assert(dfs(root, -1, 0) == 2 * (n - 1));
        for (int i = 0; i < n; i++) {
            for (int euler : euler_tour_path_queries[i]) {
                euler_tour_path_queries_rev[euler] = i;
            }
        }
        return make_pair(euler_tour_path_queries, euler_tour_path_queries_rev);
    }

    // returns node, distance from start (in terms of edges)
    pair<int, int> find_farthest_point(int start) {
        // node, parent, distance
        deque<tuple<int, int, int>> q;
        q.emplace_back(start, -1, 0);
        pair<int, int> ans = make_pair(start, 0);
        while (!q.empty()) {
            tuple<int, int, int> curr = q.front();
            q.pop_front();
            if (get<2>(curr) > ans.second) ans = make_pair(get<0>(curr), get<2>(curr));
            for (int neighbor : adj[get<0>(curr)]) {
                if (neighbor != get<1>(curr)) {
                    q.emplace_back(neighbor, get<0>(curr), get<2>(curr) + 1);
                }
            }
        }
        return ans;
    }

    int get_diameter() {
        int start = find_farthest_point(0).first;
        return find_farthest_point(start).second;
    }

private:
    static vector<vector<int>> get_adj(int n, vector<pair<int, int>> edge_list) {
        assert(edge_list.size() == n - 1);
        vector<vector<int>> adj(n, vector<int>());
        for (pair<int, int>& edge : edge_list) {
            adj[edge.first].push_back(edge.second);
            adj[edge.second].push_back(edge.first);
        }
        return adj;
    }

    // AFTER n has been read in, read in a tree of n vertices (n - 1 edges)
    static vector<vector<int>> get_adj(int n, bool one_indexed) {
        vector<vector<int>> adj(n, vector<int>());
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            if (one_indexed) {
                u--;
                v--;
            }
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        return adj;
    }
};

int min_func(int x, int y) { return min(x, y); }
class lca {
private:
    vector<vector<int>> euler_tour_path_queries;
    vector<int> euler_tour_path_queries_rev;
    sparse_table<int, min_func> stable;

    static sparse_table<int, min_func> get_sparse_table(
            vector<int>& depths,
            vector<vector<int>>& euler_tour_path_queries,
            vector<int>& euler_tour_path_queries_rev) {
        vector<int> euler_depths(euler_tour_path_queries_rev.size());
        for (int i = 0; i < (int) euler_tour_path_queries_rev.size(); i++) {
            euler_depths[i] = depths[euler_tour_path_queries_rev[i]];
        }
        return sparse_table<int, min_func>(euler_depths);
    }
    // does this unnecessarily copy stuff?
    lca(vector<int> depths, pair<vector<vector<int>>, vector<int>> euler_tour) :
            euler_tour_path_queries(euler_tour.first),
            euler_tour_path_queries_rev(euler_tour.second),
            stable(get_sparse_table(depths, euler_tour.first, euler_tour.second)) {}

public:
    explicit lca(tree &t, int root) : lca(t.get_depths(root), t.get_euler_tour_path_queries(root)) {}

    int query(int u, int v) {
        assert(!euler_tour_path_queries.empty());
        int uEuler = euler_tour_path_queries[u].front();
        int vEuler = euler_tour_path_queries[v].front();
        int ancEuler = stable.queryFirstIndex(min(uEuler, vEuler), max(uEuler, vEuler));
        return euler_tour_path_queries_rev[ancEuler];
    }
};

#endif // CPP_TREE_HPP
