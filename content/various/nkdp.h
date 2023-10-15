/**
 * Author: CF
 * Date: 2015-09-12
 * License: CC0
 * Source: CF
 * Description: Tree DP for $O(nk)$
 * Status: tested
 */

function calc_dp (u):
	for each child v of u:
		calc_dp(v)
	dp[u]=[0]
	for each child v of u:
		temp=[0,0,...,0]
		for i in 0..length(dp[u])-1:
			for j in in 0..length(dp[v])-1:
				if i+j<K:
					# calculate something 
					# typically based on dp[u][i] and dp[v][j]
					# commonly assign to temp[i + j]
		pop elements from temp until length(temp)<=K
		dp[u]=temp