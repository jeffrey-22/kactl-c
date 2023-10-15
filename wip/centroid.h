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

struct centroid {
  vector<vector<int>> edges, cent;
  vector<int> vis, par, siz;
  int n, root;
  
  centroid(int n) : n(n), edges(n), vis(n, 0), par(n), siz(n), cent(n) {} 
 
  void add_edge(int a, int b) {
    edges[a].pb(b);
    edges[b].pb(a);
  }
 
  int find_size(int v, int p = -1) {
    if (vis[v]) return 0;
    siz[v] = 1;
    for (int x: edges[v]) {
      if (x != p) siz[v] += find_size(x, v);   
    }
    return siz[v];
  }
 
  int find_centroid(int v, int p, int n) {
    for (int x: edges[v]) {
      if (x != p) {
        if (!vis[x] && siz[x] > n / 2) {
          return find_centroid(x, v, n);
        }
      }
    }
    return v;
  }
 
  void init_centroid(int v = 0, int p = -1) {
    find_size(v);
    int c = find_centroid(v, -1, siz[v]);
    vis[c] = true;
    par[c] = p;
    if(p != -1) cent[p].pb(c);
	else root = c;
 
    for (int x: edges[c]) {
      if (!vis[x]) {
        init_centroid(x, c);
      }
    }
  }
};