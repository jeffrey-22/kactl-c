/**
 * Author: CF
 * Date: 2015-09-12
 * License: CC0
 * Source: CF
 * Description: I keep coding these wrong
 * Status: tested
 */
void dijkstra(int S) {
    for(int i=1;i<=n;i++) {
        dis[i]=1000000000000000000ll;
    }
    memset(vis,0,sizeof(vis));
    priority_queue< pair<ll,int> ,vector<pair<ll,int> > ,greater< pair<ll,int> > > que;
    dis[S]=0;
    que.push({0,S});
    while(!que.empty()) {
        int now=que.top().second;
        que.pop();
        if (vis[now]) continue;
        vis[now]=1;
        for(auto i:e[now]) {
            if (dis[i.ff]>i.ss+dis[now]) {
                dis[i.ff]=i.ss+dis[now];
                que.push({dis[i.ff],i.ff});
            }
        }
    }
}