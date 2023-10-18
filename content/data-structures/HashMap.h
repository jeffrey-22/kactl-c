/**
 * Author: Simon Lindholm, chilli
 * Date: 2018-07-23
 * License: CC0
 * Source: http://codeforces.com/blog/entry/60737
 * Description: Hash map of (key:ull, value:T). Create with the highest b such that $2^b$ of entries fit in the memory limit. Faster than unordered\_map, but if not for tight constraint use unordered\_map for stability.
 */
#pragma once

typedef uint64_t ull;                                                                                                                
template<class T>
struct HashMap {
    int b;
    vector<pair<ull, T>> v;
    HashMap(int b) : b(b), v(1 << b) {}
    T& operator[](ull x) {
        ull y = x >> (64 - b), m = (1 << b) - 1;
        while (v[y].first && v[y].first != x) ++y &= m;
        v[y].first = x;
        return v[y].second;
    }   
};