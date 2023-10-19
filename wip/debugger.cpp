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
    DinicMCMF f(5);
    auto e1 = f.addEdge(4, 0, 9, 9); // 4 - 6
    auto e2 = f.addEdge(4, 2, 6, 6); // 6 - 6
    auto e3 = f.addEdge(1, 0, 3, 1); // 3 - 1
    auto e4 = f.addEdge(2, 3, 8, 2); // 8 - 8
    auto e5 = f.addEdge(4, 1, 3, 6); // 5 - 3
    auto e6 = f.addEdge(0, 3, 7, 2); // 7 - 7
    auto e7 = f.addEdge(1, 2, 2, 5); // 2 - 2
    cout << f.calc(4, 3).ss << endl;
    cout << f.getflow(e1) << endl;
    cout << f.getflow(e2) << endl;
    cout << f.getflow(e3) << endl;
    cout << f.getflow(e4) << endl;
    cout << f.getflow(e5) << endl;
    cout << f.getflow(e6) << endl;
    cout << f.getflow(e7) << endl;
}