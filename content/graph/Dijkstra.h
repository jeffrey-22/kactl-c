/**
 * Author: CF
 * Date: 2015-09-12
 * License: CC0
 * Source: CF
 * Description: Takes in the graph (to, len) and returns the distance vector. inf if unreachable from s. $O(m\log m)$
 * Status: tested
 */
const ll inf = 1e18 + 5;
vector<ll> dijkstra(const vector<vector<pair<int, ll>>> &g, int s) {
  vector<ll> d(sz(g), inf); // sz(g) + 1 for 1-indexed graph
  vector<int> vis(sz(g));
  priority_queue< pair<ll,int>, vector<pair<ll,int> >, greater< pair<ll,int> > > q;
  d[s]=0;
  q.push({0, s});
  while(!q.empty()) {
    int u = q.top().ss; q.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for(auto i : g[u])
      if (d[i.ff] > i.ss + d[u])
        d[i.ff] = i.ss + d[u], q.push({d[i.ff], i.ff});
  }
  return d;
}