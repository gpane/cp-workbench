#ifndef CURRENT_DAG_CPP
#define CURRENT_DAG_CPP

#include <deque>
#include <iostream>
#include <vector>

using namespace std;

// WARNING: untested
class dag {
public:
    const int num_vertices;
    const int num_edges;
    const vector<vector<int>> adj;

    dag(int num_vertices, vector<pair<int, int>> &edge_list) :
            num_vertices(num_vertices),
            num_edges(edge_list.size()),
            adj(get_adj(num_vertices, edge_list)) {};

    dag(int num_vertices, int num_edges, bool one_indexed) :
            num_vertices(num_vertices),
            num_edges(num_edges),
            adj(get_adj(num_vertices, num_edges, one_indexed)) {};

    dag(int num_vertices, int num_edges) : dag(num_vertices, num_edges, true) {};

    // untested
    vector<int> topological_sort() {
        vector<int> in_degrees(num_vertices);
        for (const vector<int>& children : adj) {
            for (int child : children) in_degrees[child]++;
        }

        deque<int> q;
        for (int i = 0; i < num_vertices; i++) {
            if (in_degrees[i] == 0) {
                q.push_back(i);
            }
        }

        vector<int> ans(num_vertices, -1);
        int index = 0;
        while (!q.empty()) {
            int curr = q.front(); q.pop_front();
            ans[index++] = curr;
            for (int child : adj[curr]) {
                in_degrees[child]--;
                if (in_degrees[child] == 0) {
                    q.push_back(child);
                }
            }
        }
        for (int i = 0; i < num_vertices; i++) {
            if (ans[i] < 0) return vector<int>();
        }
        return ans;
    }

    // untested
    vector<int> get_sizes(const vector<int>& top_sorted) {
        vector<int> ans(num_vertices, 1);
        for (int i = num_vertices - 1; i >= 0; i--) {
            int u = top_sorted[i];
            for (int child : adj[u]) {
                ans[u] += ans[child];
            }
        }
        return ans;
    }

    vector<int> get_sizes() {
        return get_sizes(topological_sort());
    }

private:
    static vector<vector<int>> get_adj(int num_vertices, vector<pair<int, int>>& edge_list) {
        vector<vector<int>> adj(num_vertices, vector<int>());
        for (pair<int, int>& edge : edge_list) {
            adj[edge.first].push_back(edge.second);
        }
        return adj;
    }

    static vector<vector<int>> get_adj(int num_vertices, int num_edges, bool one_indexed) {
        vector<vector<int>> adj(num_vertices, vector<int>());
        for (int i = 0; i < num_edges; i++) {
            int u, v;
            cin >> u >> v;
            if (one_indexed) {
                u--; v--;
            }
            adj[u].push_back(v);
        }
        return adj;
    }
};


#endif //CURRENT_DAG_CPP
