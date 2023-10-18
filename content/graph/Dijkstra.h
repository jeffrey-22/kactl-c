/**
 * Author: CF
 * Date: 2015-09-12
 * License: CC0
 * Source: CF
 * Description: I keep coding these wrong
 * Status: tested
 */
const ll inf = 1000000000000000000ll;
void dijkstra(int s) {
  for(int i = 1; i <= n; i++) dis[i] = inf;
  memset(vis, 0, sizeof(vis));
  priority_queue< pair<ll,int> ,vector<pair<ll,int> > ,greater< pair<ll,int> > > q;
  dis[s]=0;
  q.push({0, s});
  while(!q.empty()) {
    int u=q.top().ss;
    q.pop();
    if (vis[u]) continue;
    vis[u]=1;
    for(auto i : e[u])
      if (dis[i.ff] > i.ss + dis[u]) {
        dis[i.ff] = i.ss + dis[u];
        q.push({dis[i.ff], i.ff});
      }
  }
}