#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;
//#define mp make_pair
#define pb push_back
#define eb emplace_back
#define ti tuple<ll,ll,ll>
#define ff first 
#define ss second
#define rep(i,a,b) for(ll i=(a); i<(b); i++)
#define repd(i,a,b) for(ll i=(a)-1; i!=(b)-1; i--)
#define all(x) x.begin(),x.end()
#define sz(a) ((int) (a).size())
#define me(a, x) memset(a, x, sizeof(a))
#define nl '\n'
#define cma <<','<<

typedef vector<int> vi;
#include "../content/graph/MinCostMaxFlowSlow.h"
#include "../content/graph/DinicMCMF.h"

tuple<int, int, int, int> e[100009];
int main() {
    srand(0);
    int n = 100, m = 1000, capmax = 1000000, costmax = 1000000, s, t;
    ll a, b, c, d;
    do {
        MinCostMaxFlowSlow f1(n);
        DinicMCMF f2(n);
        rep(i, 0, m) {
            int u = rand() % n;
            int v = rand() % n;
            int cap = rand() % capmax;
            int cost = rand() % costmax;
            f1.addEdge(u, v, cap, cost);
            f2.addEdge(u, v, cap, cost);
            e[i] = {u, v, cap, cost};
        }
        s = rand() % n, t;
        do {
            t = rand() % n;
        } while (s == t); 
        tie (a, b) = f1.mcmf(s, t);
        tie (c, d) = f2.calc(s, t);
    } while (a == c && b == d);
    cout << s << " " << t << endl;
    rep(i, 0, m) {
        auto [u, v, cap, cost] = e[i];
        cout << "f.addEdge(" << u << ", " << v << ", " << cap << ", " << cost << ");" << endl;
    }
    cout << a << " " << b << " " << c << " " << d << endl;
}