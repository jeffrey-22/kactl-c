/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
#pragma once

struct Dinic {
  struct Edge {
    int to, rev;
    ll c, oc;
  };
  vi d, ptr, q;
  vector<vector<Edge>> g;
  Dinic(int n) : d(n), ptr(n), q(n), g(n) {}
  pair<int, int> addEdge(int a, int b, ll c) {
    g[a].push_back({b, sz(g[b]), c, c});
    g[b].push_back({a, sz(g[a]) - 1, 0ll, 0ll});
    return {a, sz(g[a]) - 1};
  }
  ll getflow(pair<int, int> x) { Edge e = g[x.ff][x.ss]; return max(e.oc - e.c, 0ll); }
  ll dfs(int v, int t, ll f) {
    if (v == t || !f) return f;
    for (int& i = ptr[v]; i < sz(g[v]); i++) {
      Edge& e = g[v][i];
      if (d[e.to] == d[v] + 1)
        if (ll p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, g[e.to][e.rev].c += p;
          return p;
        }
    }
    return 0;
  }
  ll calc(int s, int t) {
    ll flow = 0; q[0] = s;
    rep(L,0,31) do { // 'int L=30' maybe faster for random data
      d = ptr = vi(sz(q));
      int qi = 0, qe = d[s] = 1;
      while (qi < qe && !d[t]) {
        int v = q[qi++];
        for (Edge e : g[v])
          if (!d[e.to] && e.c >> (30 - L))
            q[qe++] = e.to, d[e.to] = d[v] + 1;
      }
      while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
    } while (d[t]);
    return flow;
  }
  bool isVertexOnTheLeftOfMinCut(int a) { return d[a] != 0; }
};
