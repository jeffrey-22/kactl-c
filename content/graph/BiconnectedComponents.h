/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Finds all biconnected components in an undirected graph, and
 *  runs a callback for the edges in each. In a biconnected component there
 *  are at least two distinct paths between any two nodes. Note that a node can
 *  be in several components. An edge which is not in a component is a bridge,
 *  i.e., not part of any cycle.
 * Usage:
 *  int eid = 0; ed.resize(N);
 *  for each edge (a,b) {
 *    ed[a].emplace_back(b, eid);
 *    ed[b].emplace_back(a, eid++); }
 *  bicomps([\&](const vi\& edgelist) {...});
 * Time: O(E + V)
 */
#pragma once

//cnt is number of BCC; all vertices joined to n+i are in the same BCC
struct BlockCutTree {
    int n;
    vector<vector<int>> adj;
    vector<int> tin, low, stk;
    int cnt, cur;
    vector<pair<int, int>> edges;
    BlockCutTree(int n): n(n), adj(n), tin(n, -1), low(n), stk(0), cnt(0), cur(0), edges(0) {}
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int x) {
        stk.push_back(x);
        tin[x] = low[x] = cur++;
        for (auto y : adj[x]) {
            if (tin[y] == -1) {
                dfs(y);
                low[x] = min(low[x], low[y]);
                if (low[y] == tin[x]) {
                    int v;
                    while(v != y){
                        v = stk.back();
                        stk.pop_back();
                        edges.emplace_back(n + cnt, v);
                    }
                    edges.emplace_back(x, n + cnt);
                    cnt++;
                }
            } else low[x] = min(low[x], tin[y]);
        }
    }
    pair<int, vector<pair<int, int>>> work() {
        dfs(1);
        return {cnt, edges};
    }
};