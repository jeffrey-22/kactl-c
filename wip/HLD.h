/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and max queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * Takes as input the full adjacency list. VALS\_EDGES being true means that
 * values are stored in the edges, as opposed to the nodes. All values
 * initialized to the segtree default. Root must be 0.
 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */
#pragma once

#include "../data-structures/LazySegmentTree.h"

struct HLD {
    int n, cur;
    vector<int> siz, top, dep, parent, in, out, seq;
    vector<vector<int>> adj;
    
    HLD(int n) : n(n), siz(n), top(n), dep(n), parent(n, -1), in(n), out(n), seq(n), adj(n), cur(0) {}
    void add_edge(int u, int v) {
        adj[u].pb(v); adj[v].pb(u);
    }
    void work(int root = 0) {
        top[root] = root; dep[root] = 0;
        parent[root] = -1;
        dfs1(root); dfs2(root);
    }
    void dfs1(int u) {
        if (parent[u] != -1)  adj[u].erase(find(all(adj[u]), parent[u]));
        siz[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) swap(v, adj[u][0]);
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur - 1;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) u = parent[top[u]];
			else v = parent[top[v]];
        }
        return dep[u] < dep[v] ? u : v;
    }
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    int jump(int u, int k) {
        if (dep[u] < k) return -1;
        int d = dep[u] - k;
        while (dep[top[u]] > d) u = parent[top[u]];
        return seq[in[u] - dep[u] + d];
    }
    //is u ancestor of v
    bool isanc(int u, int v) {
        return in[u] <= in[v] && out[u] >= out[v];
    }
    // child of u that is ancestor of v
    int rootedChild(int u, int v) {
        if (u == v) return u;
        if (!isanc(u, v)) return parent[u];
        auto it = upper_bound(all(adj[u]), v, [&](int x, int y) {
            return in[x] < in[y];
        }) - 1;
        return *it;
    }
    //size of subtree of v when rooted at u
    int rootedSize(int u, int v) {
        if (u == v) return n;
        if (!isanc(v, u)) return siz[v];
        return n - siz[rootedChild(v, u)];
    }
    
    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};
