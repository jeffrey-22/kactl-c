/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: Wavelet Tree
 * Status: tested as part of DirectedMST.h
 */
#pragma once

struct wavelet_tree{
    int low, high;
    wavelet_tree *l, *r;
    vector<int> freq;
    wavelet_tree(int* from, int* to, int x, int y)
    {
        low = x, high = y;
        if (from >= to)
            return;
        if (high == low) {
            freq.reserve(to - from + 1);
            freq.push_back(0);
            for (auto it = from; it != to; it++)
                freq.push_back(freq.back() + 1);
            return;
        }
        int mid = (low + high) / 2;
        auto lessThanMid = [mid](int x) {
            return x <= mid;
        };
        freq.reserve(to - from + 1);
        freq.push_back(0);
        for (auto it = from; it != to; it++)
            freq.push_back(freq.back() + lessThanMid(*it));       
        auto pivot = stable_partition(from, to, lessThanMid);
        l = new wavelet_tree(from, pivot, low, mid);
        r = new wavelet_tree(pivot, to, mid + 1, high);
    }
 
     //no. of elements in [l,r] less than or equal to k
    int kOrLess(int l, int r, int k)
    {
        if (l > r or k < low)
            return 0;
        if (high <= k)
            return r - l + 1;
        int lb = freq[l - 1];
        int rb = freq[r];
        return (this->l->kOrLess(lb + 1, rb, k) +
             this->r->kOrLess(l - lb, r - rb, k));
    }
    
    //kth smallest element in [l,r]
    int kthsmallest(int l, int r, int k){
        if(l > r) return 0;
        if(low == high) return low;
        int inLeft = freq[r] - freq[l-1];
        int lb = freq[l-1];
        int rb = freq[r];
        if(k <= inLeft) return this->l->kthsmallest(lb+1,rb,k);
        return this->r->kthsmallest(l-lb,r-rb,k-inLeft);
    }
    
    //count in [l,r] equal to k
    int count(int l, int r, int k){
        if(l < k || k < low || k > high) return 0;
        if(low == high) return r-l+1;
        int lb = freq[l-1], rb = freq[r], mid = (low+high)/2;
        if(k<=mid) return this->l->count(lb+1,rb,k);
        return this->r->count(l-lb,r-rb,k);
    }
};