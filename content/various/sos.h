/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Sum over subsets
 * Time: $O(3^n)$
 */
#pragma once

for (int i = 0; i < (1 << n); i++)
	// iterate over all subsets of i directly
	for (int j = (i - 1) & i; j >= 0; j = (j - 1) & i) sos[i] += a[j];