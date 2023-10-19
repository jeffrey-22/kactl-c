/**
 * Author: Alon Krymgand
 * Date: 2023-10-02
 * Source: Haifa's Algorithm Competition Template Library
 * Description: Min-cost max-flow. Faster than Dinic based MCMF somehow.
 * Status: Tested.
 * Time: $O(F * E \log V)$, and $O(VE + F * E \log V)$ if contains negative cost
 * edges, where $F$ is the maxmimum flow value. Can easily TLE, test max inputs.
 * before submitting!
 */
#pragma once

template<typename F, typename C>
struct MCMF {
  struct Edge {
    int to;
    F cap;
    C cost;
    int id;
    Edge() : to(), cap(), cost(), id(){}
    Edge(int _to, F _cap, C _cost, int _id){
      to = _to; cap = _cap; cost = _cost; id = _id;   
    }
  };
  int n;
  vector<Edge> E;
  vector<vector<int> > G;
  vector<int> par, use;
  vector<C> dis, pot;
  MCMF(int _n) : n(_n), use(_n, 0), pot(_n, 0) {
    G.resize(_n);
    dis.resize(_n);
    par.resize(_n);
  }
  void addEdge(int u, int v, F cap, C cost, int id = -1){
    G[u].pb(E.size());
    E.pb({v, cap, cost, id});
    G[v].	pb(E.size());;
    E.pb({u, 0, -cost, id});
  }
  pair<F, C> push(int src, int snk){
    fill(all(dis), numeric_limits<C>::max());
    fill(all(par), -1);
    fill(all(use), 0);
    // priority_queue<pair<C, int>, vector<pair<C, int> >, greater<pair<C, int> > > pq;
    queue<pair<C, int>> pq;
    dis[src] = 0;
    pq.push({0, src});
    int fr;
    while(!pq.empty()){
      fr = pq.front().ss; pq.pop();
      if(use[fr]) continue;
      use[fr] = 1;
      for(auto id : G[fr]){
        if(E[id].cap == 0) continue;
        C w = E[id].cost;
        if(dis[E[id].to] > dis[fr] + w){
          dis[E[id].to] = dis[fr] + w;
          if(E[id].to != snk){
            pq.push({dis[E[id].to], E[id].to});
          } else use[snk] = 1;
          par[E[id].to] = id;
        }
      }
    }
    if(use[snk] == 0) return {0, 0};
    F mn = numeric_limits<F>::max();
    for(int u = snk; ~par[u]; u = E[par[u] ^ 1].to) mn = min(mn, E[par[u]].cap);
    for(int u = snk; ~par[u]; u = E[par[u] ^ 1].to) E[par[u]].cap -= mn, E[par[u] ^ 1].cap += mn;
    return {mn, dis[snk]};
  }

  pair<F, C> mincost(int src, int snk){
    pair<F, C> res, tot = {0, 0};
    while((res = push(src, snk)).ff){
      tot.ss += res.ff * res.ss;
      tot.ff += res.ff;
    }
    return tot;
  }
};