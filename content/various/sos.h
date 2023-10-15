/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Sum over subsets, F[mask] is sum of A[x] such that x is a subset of mask
 * Time: $O(n\cdot 2^n), O(3^n)$
 */
#pragma once

for(int i = 0; i<(1<<N); ++i)
	F[i] = A[i];
for(int i = 0;i < N; ++i) 
    for(int mask = 0; mask < (1<<N); ++mask)
        if(mask & (1<<i))
            F[mask] += F[mask^(1<<i)];
// -----------------
for (int i = 0; i < (1 << n); i++)
	for (int j = (i - 1) & i; j >= 0; j = (j - 1) & i)
        F[i] += A[j];