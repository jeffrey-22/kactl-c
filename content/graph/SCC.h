/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Usage: scc(graph, [\&](vi\& v) { ... }) visits all components
 * in reverse topological order. comp[i] holds the component
 * index of a node (a component only has edges to components with
 * lower index). ncomps will contain the number of components.
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */
#pragma once

struct SCC {
    int n;
    vector<vector<int>> adj;
    vector<int> stk, dfn, low, bel;
    int cur, cnt;
    
    SCC(int n): n(n), adj(n), dfn(n, -1), low(n), bel(n, -1), stk(0), cur(0), cnt(0) {}
    
    void add_edge(int u, int v){
    	adj[u].push_back(v);
	}
    
    void dfs(int x) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        for (auto y : adj[x]) {
            if (dfn[y] == -1) {
                dfs(y); 
				low[x] = min(low[x], low[y]);
            } else if (bel[y] == -1) low[x] = min(low[x], dfn[y]);
        }
        if (dfn[x] == low[x]) {
            int y = -1;
            while(y != x) {
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            }
            cnt++;
        }
    }
    vector<int> work() {
        for (int i = 0; i < n; i++) if(dfn[i] == -1) dfs(i);
        return bel;
    }
};
