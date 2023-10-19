/**
 * Author: Alon Krymgand
 * Date: 2023-10-02
 * Source: Haifa's Algorithm Competition Template Library
 * Description: Min-cost max-flow. Slower than DinicMCMF so prioritize that unless negative cost is needed. Duplicated edges allowed, negative cycles not
 * supported. To obtain the actual flow, look at positive values only.
 * Status: Tested.
 * Time: $O(F * E \log V)$, and $O(VE + F * E \log V)$ if contains negative cost
 * edges, where $F$ is the maxmimum flow value. Can easily TLE, test max inputs.
 * before submitting!
 */
#pragma once

const ll inf = 1e18 + 5;
struct MinCostMaxFlowSlow {
  struct Edge {
    int to, rev;
    ll cap, oc, cost;
  };
  int n;
  vector<vector<Edge>> g;
  vi par, eid;
  vector<ll> pi;
  MinCostMaxFlowSlow(int n) : n(n), g(n), par(n), eid(n), pi(n) {}
  pair<int, int> addEdge(int a, int b, ll cap, ll cost) {
    g[a].push_back({b, sz(g[b]), cap, cap, cost});
    g[b].push_back({a, sz(g[a]) - 1, 0, 0, -cost});
    return {a, sz(g[a]) - 1};
  }
  ll getflow(pair<int, int> x) { Edge e = g[x.ff][x.ss]; return max(e.oc - e.cap, 0ll); }
  bool augment(int s, int t) {
    vector<ll> d(n, inf);
    vector<bool> inq(n);
    queue<int> q;
    q.push(s), inq[s] = true, d[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop(), inq[u] = 0;
      rep(i, 0, sz(g[u])) {
        auto e = g[u][i];
        ll dto = d[u] - pi[e.to] + pi[u] + e.cost;
        if (e.cap > 0 && dto < d[e.to]) {
          d[e.to] = dto;
          par[e.to] = u;
          eid[e.to] = i;
          if (!inq[e.to])
            q.push(e.to), inq[e.to] = true;
        }
      }
    }
    return d[t] != inf;
  }
  pair<ll, ll> mcmf(int s, int t) {
    ll maxf = 0, minc = 0;
    while (augment(s, t)) {
      ll f = inf, costsum = 0;
      for (int p = t; p != s; p = par[p]) {
        auto &e = g[par[p]][eid[p]];
        f = min(f, e.cap);
        costsum += e.cost;
      }
      for (int p = t; p != s; p = par[p]) {
        auto &e = g[par[p]][eid[p]];
        e.cap -= f;
        g[e.to][e.rev].cap += f;
      }
      maxf += f, minc += costsum * f;
    }
    return {maxf, minc};
  }
  bool setpi(int s) {
    // call before mcmf, if there are negative costs.
    // Uses Bellman-Ford to compute pi of vertices in O(nm).
    pi.assign(n, inf), pi[s] = 0;
    int it = n, ch = 1;
    ll v;
    while (ch-- && it--) {
      rep(u, 0, n) for (auto &e : g[u]) {
        if (e.cap != 0 && (v = pi[u] + e.cost) < pi[e.to])
          ch = 1, pi[e.to] = v;
      }
    }
    return it >= 0; // true if NO negative cycles found
  }
};