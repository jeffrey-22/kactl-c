/**
 * Author: Me
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Min Cost Max Flow based on Dijkstra and Dinic. Does not support negative cycles. Support duplicated edges.
 * Time: $O(F * E \log V)$, where $F$ is the maxmimum flow value. $O(VE + F * E \log V)$ if contains negative cost
 * edges, where $F$ is the maxmimum flow value.
 */
#pragma once

const ll inf = 1e18 + 5;
struct MinCostMaxFlow {
  struct Edge {
    int to, rev;
    ll c, oc, w;
  };
  vi ptr, vis, q;
  vector<ll> d;
  vector<vector<Edge>> g;
  typedef pair<ll,int> pli;
  MinCostMaxFlow(int n) : ptr(n), vis(n), q(n), d(n), g(n) {}
  pair<int, int> addEdge(int a, int b, ll c, ll cost) {
    g[a].push_back({b, sz(g[b]), c, c, cost});
    g[b].push_back({a, sz(g[a]) - 1, 0ll, 0ll, -cost});
    return {a, sz(g[a]) - 1};
  }
  ll getflow(pair<int, int> x) { Edge e = g[x.ff][x.ss]; return max(e.oc - e.c, 0ll); }
  ll dfs(int v, int t, ll f) {
    if (v == t || !f) return f;
    for (int& i = ptr[v]; i < sz(g[v]);) {
      Edge& e = g[v][i++];
      if (d[e.to] == e.w + d[v])
        if (ll p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, g[e.to][e.rev].c += p;
          return p;
        }
    }
    return 0;
  }
  pair<ll, ll> calc(int s, int t) {
    ll flow = 0, totcost = 0; q[0] = s;
    while(1) {
      ptr = vi(sz(g));
      d = vector<ll>(sz(g), inf);
      int qi = d[s] = 0, qe = vis[s] = 1;
      while (qi < qe) {
        int v = q[qi++];
        vis[v] = 0;
        for (Edge e : g[v])
          if (e.c && d[e.to] > e.w + d[v]) {
            d[e.to] = e.w + d[v];
            if (!vis[e.to]) {
              vis[e.to] = 1;
              if (sz(q) == qe) q.pb(e.to); else q[qe] = e.to;
              qe++;
            }
          }
      }
      if (d[t] == inf) break;
      while (ll p = dfs(s, t, LLONG_MAX)) flow += p, totcost += p * d[t];
    }
    return {flow, totcost};
  }
};
