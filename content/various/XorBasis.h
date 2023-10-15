/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: XorBasis
 * Time: $O(lg(N))$
 */
#pragma once

const int lg = 30;
struct basis{
	vector<int> v;
	int siz;
	basis(): v(lg, 0), siz(0){}
	void insert(ll mask){
		for(int i = lg - 1; i >= 0; i--){
			if((mask >> i & 1) == 0) continue;
			if(!v[i]){
				v[i] = mask; siz++;
				return;	
			}
			mask ^= v[i];
		}
	}
	bool canrep(ll x){
		repd(i,lg,0){
			if(x >> i & 1 == 0) continue;
			if(!v[i]) return false;
			x ^= v[i];
		}
		return true;
	}
	ll getmx(){
		ll res = 0;
		for(int i = lg -1; i >= 0; i--){
			if(!v[i] || (res >> i & 1)) continue;
			res ^= v[i];
		}
		return res;
	}
};
