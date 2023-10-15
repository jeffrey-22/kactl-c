/**
 * Author: CF
 * Date: 2015-09-12
 * License: CC0
 * Source: CF
 * Description: Tree DP for $O(nk)$
 * Status: tested
 */
vector<vector<int>> dp;
void calc_dp(int u, int K, vector<vector<int>> &e) {
	for (auto v : e[u])
		calc_dp(v, K, e);
	dp[u].clear(); dp[u].pb(0);
	for (auto v : e[u]) {
        vector<int> temp(K, 0);
		rep(i, 0, sz(dp[u])):
		    rep(j, 0, sz(dp[v])):
				if (i + j < K) {
					// calculate something 
					// typically based on dp[u][i] and dp[v][j]
					// commonly assign to temp[i + j]
                }
        while (sz(temp) > K) temp.pop_back();
        dp[u] = temp;
    }
}